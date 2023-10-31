#include "Sketch.hpp"

Sketch::Sketch(SDL_Renderer* renderer) : renderer_(renderer) { setup(); }

void Sketch::setup() {}

void Sketch::update(const double& delta_time) {}

void Sketch::draw() const noexcept {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);

    // draw filled circle in the middle of the screen
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    int radius = std::min(window_width_, window_height_) / 3;
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer_, window_width_ / 2 + x, window_height_ / 2 + y);
            }
        }
    }

    SDL_RenderPresent(renderer_);
}

void Sketch::set_window_size(const int& width, const int& height) noexcept {
    window_width_ = width;
    window_height_ = height;
}
