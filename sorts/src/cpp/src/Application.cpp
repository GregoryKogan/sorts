#include "Application.hpp"

Application::Application() {
    int width, height;
    SDL_GetWindowSize(window_, &width, &height);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE | SDL_RENDERER_ACCELERATED, &window_, &renderer_);

    if (!window_ || !renderer_) {
        std::cout << "Failed to create window and renderer\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    sketch_ = std::make_unique<Sketch>(renderer_);

    last_time_ = SDL_GetTicks64();
}

Application::~Application() { SDL_DestroyWindow(window_); }

void Application::loop() {
    while (keep_window_open_) {
        handle_window_events_();
        handle_messages_();

        sync_data_();

        double delta_time = get_delta_time_();
        if (delta_time < 16) SDL_Delay(16 - delta_time);

        sketch_->update(delta_time);
        sketch_->draw();
    }
}

void Application::handle_window_events_() {
    while (SDL_PollEvent(&window_event_) > 0) {
        switch (window_event_.type) {
            case SDL_QUIT:
                keep_window_open_ = false;
                break;
            case SDL_WINDOWEVENT:
                switch (window_event_.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        sketch_->set_window_size(window_event_.window.data1, window_event_.window.data2);
                        break;
                }
                break;
        }
    }
}

void Application::handle_messages_() {
    if (Messenger::instance().has_message()) {
        std::string message = Messenger::instance().get_message();
        std::cout << "Message: " << message << "\n";
    }
}

double Application::get_delta_time_() {
    Uint64 current_time = SDL_GetTicks64();
    Uint64 delta_time = current_time - last_time_;
    last_time_ = current_time;
    delta_time_records_.push_back(delta_time);
    if (delta_time_records_.size() > max_delta_time_records_) delta_time_records_.pop_front();
    return (double)delta_time;
}

void Application::sync_data_() {
    Uint64 current_time = SDL_GetTicks64();
    if (current_time - last_data_sync_time_ < data_sync_period_) return;
    last_data_sync_time_ = current_time;

    send_frame_rate_();
}

void Application::send_frame_rate_() {
    rapidjson::Document message_doc;
    message_doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = message_doc.GetAllocator();
    {
        message_doc.AddMember("to", "js", allocator);
        rapidjson::Value message_obj;
        message_obj.SetObject();
        { message_obj.AddMember("frame_rate", get_frame_rate(), allocator); }
        message_doc.AddMember("message", message_obj, allocator);
    }
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    message_doc.Accept(writer);
    std::string json_string = buffer.GetString();

    Messenger::instance().send_message(json_string);
}

Uint64 Application::get_frame_rate() const noexcept {
    if (!delta_time_records_.size()) return 0;

    Uint64 sum = 0;
    for (Uint64 delta_time : delta_time_records_) sum += delta_time;
    Uint64 average_delta_time = sum / delta_time_records_.size();
    if (!average_delta_time) return 0;
    return 1000 / average_delta_time;
}
