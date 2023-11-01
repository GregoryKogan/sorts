#ifndef SKETCH_HPP
#define SKETCH_HPP

#include <SDL2/SDL.h>

#include <cmath>
#include <iostream>

#include "../../sorts/smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../../sorts/sorters/BaseSorter.hpp"
#include "../../sorts/sorters/BubbleSorter/BubbleSorter.hpp"
#include "../../sorts/sorters/SelectionSorter/SelectionSorter.hpp"

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

    float vertical_scale_ = 0.0f;
    float horizontal_scale_ = 0.0f;

    u_int32_t comparisons_per_second_ = 200000;
    u_int32_t milliseconds_since_last_sort_ = 0;
    u_int32_t min_comparisons_to_sort_ = std::min((u_int32_t)1, comparisons_per_second_ / 60);

    std::size_t seq_len_ = 2000;
    std::size_t max_value_ = 1000;
    kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence_;

    kogan::UniquePtr<kogan::Sorter<int>> sorter_;

    void generate_sequence_() noexcept;

    void draw_value_(int index, bool sorted = false, bool interesting = false) const noexcept;
};

#endif