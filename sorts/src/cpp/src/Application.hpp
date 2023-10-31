#include <SDL2/SDL.h>

#include <deque>
#include <iostream>

#include "Sketch/Sketch.hpp"
#include "messaging/messaging.hpp"

class Application {
   public:
    Application();
    ~Application();

    void loop();

    Uint64 get_frame_rate() const noexcept;

   private:
    std::unique_ptr<Sketch> sketch_;

    SDL_Window *window_;
    SDL_Renderer *renderer_;
    SDL_Event window_event_;

    bool keep_window_open_ = true;

    Uint64 last_time_ = 0;
    std::deque<Uint64> delta_time_records_;
    std::size_t max_delta_time_records_ = 50;

    Uint64 data_sync_period_ = 1000;
    Uint64 last_data_sync_time_ = 0;

    void handle_window_events_();
    void handle_messages_();

    double get_delta_time_();

    void sync_data_();
    void send_frame_rate_();
};