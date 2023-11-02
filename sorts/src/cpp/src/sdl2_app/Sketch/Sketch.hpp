#ifndef SKETCH_HPP
#define SKETCH_HPP

#include <SDL2/SDL.h>

#include <cmath>
#include <iostream>

#include "../../sorts/smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../../sorts/sorters/BaseSorter.hpp"
#include "../../sorts/sorters/BubbleSorter/BubbleSorter.hpp"
#include "../../sorts/sorters/InsertionSorter/InsertionSorter.hpp"
#include "../../sorts/sorters/IterativeMergeSorter/IterativeMergeSorter.hpp"
#include "../../sorts/sorters/MergeSorter/MergeSorter.hpp"
#include "../../sorts/sorters/SelectionSorter/SelectionSorter.hpp"

class Sketch {
   public:
    Sketch(SDL_Renderer *renderer);

    // Lifecycle
    void setup();
    void update(const double &delta_time);
    void draw() const noexcept;

    void set_window_size(const int &width, const int &height) noexcept;

    // Observers
    u_int32_t get_comparisons() const noexcept;
    u_int32_t get_swaps() const noexcept;

    // Modifiers
    void set_sort_algorithm(const std::string &algorithm) noexcept;
    void set_comparisons_per_second(const u_int32_t &comparisons_per_second) noexcept;
    void set_sequence_length(const std::size_t &seq_len) noexcept;

   private:
    SDL_Renderer *renderer_;
    int window_width_ = 0;
    int window_height_ = 0;

    std::string sort_algorithm_ = "bubble";
    void init_sorter_() noexcept;

    bool is_setup_ = false;

    float vertical_scale_ = 0.0f;
    float horizontal_scale_ = 0.0f;
    int bottom_offset_ = 5;
    void calculate_scales_() noexcept;

    u_int32_t comparisons_per_second_ = 0;
    u_int32_t milliseconds_since_last_sort_ = 0;
    u_int32_t min_comparisons_to_sort_ = 0;

    std::size_t seq_len_ = 0;
    std::size_t max_value_ = 0;
    kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence_;

    kogan::UniquePtr<kogan::Sorter<int>> sorter_;

    void generate_sequence_() noexcept;

    void draw_value_(int index, bool sorted = false, bool interesting = false) const noexcept;
};

#endif