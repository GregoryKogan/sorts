#ifndef SKETCH_HPP
#define SKETCH_HPP

#include <SDL2/SDL.h>

#include <iostream>

class Sketch {
   public:
    Sketch(SDL_Renderer *renderer);

    void setup();
    void update(const double &delta_time);
    void draw() const noexcept;
    void set_window_size(const int &width, const int &height) noexcept;

   private:
    SDL_Renderer *renderer_;
    int window_width_ = 0;
    int window_height_ = 0;
};

#endif