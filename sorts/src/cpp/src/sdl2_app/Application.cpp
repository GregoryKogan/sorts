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

  send_ready_();
}

Application::~Application() { SDL_DestroyWindow(window_); }

void Application::loop() {
  handle_window_events_();
  handle_messages_();

  sync_data_();

  double delta_time = get_delta_time_();
  sketch_->update(delta_time);
  sketch_->draw();
}

void Application::handle_window_events_() {
  while (SDL_PollEvent(&window_event_) > 0) {
    switch (window_event_.type) {
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
  if (!Messenger::instance().has_message()) return;

  std::string message = Messenger::instance().get_message();

  rapidjson::Document message_doc;
  message_doc.Parse(message.c_str());

  if (message_doc.HasMember("action")) {
    if (message_doc["action"].GetString() == std::string("quit")) emscripten_cancel_main_loop();

    if (message_doc["action"].GetString() == std::string("sort")) {
      if (!message_doc.HasMember("algorithm") || !message_doc.HasMember("seq_len") ||
          !message_doc.HasMember("steps_per_sec") || !message_doc.HasMember("reverse_input"))
        return;
      if (!message_doc["algorithm"].IsString() || !message_doc["seq_len"].IsUint() ||
          !message_doc["steps_per_sec"].IsUint() || !message_doc["reverse_input"].IsBool())
        return;

      sketch_->set_sort_algorithm(message_doc["algorithm"].GetString());
      sketch_->set_sequence_length(message_doc["seq_len"].GetUint());
      sketch_->set_steps_per_second(message_doc["steps_per_sec"].GetUint());
      sketch_->set_reverse_input(message_doc["reverse_input"].GetBool());

      sketch_->setup();
    }
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

  send_data_();
}

void Application::send_data_() {
  rapidjson::Document message_doc;
  message_doc.SetObject();
  rapidjson::Document::AllocatorType &allocator = message_doc.GetAllocator();
  {
    message_doc.AddMember("to", "js", allocator);
    rapidjson::Value message_obj;
    message_obj.SetObject();
    {
      message_obj.AddMember("frame_rate", get_frame_rate(), allocator);
      message_obj.AddMember("comparisons", sketch_->get_comparisons(), allocator);
      message_obj.AddMember("swaps", sketch_->get_swaps(), allocator);
    }
    message_doc.AddMember("message", message_obj, allocator);
  }
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  message_doc.Accept(writer);
  std::string json_string = buffer.GetString();

  Messenger::instance().send_message(json_string);
}

void Application::send_ready_() {
  rapidjson::Document message_doc;
  message_doc.SetObject();
  rapidjson::Document::AllocatorType &allocator = message_doc.GetAllocator();
  {
    message_doc.AddMember("to", "js", allocator);
    rapidjson::Value message_obj;
    message_obj.SetObject();
    { message_obj.AddMember("app_is_ready", true, allocator); }
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
