#pragma once

#include <SDL2/SDL.h>

#include <cmath>
#include <iostream>

#include "../../sorts/smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../../sorts/sorters/BaseSorter.hpp"
#include "../../sorts/sorters/BogoSorter/BogoSorter.hpp"
#include "../../sorts/sorters/BubbleSorter/BubbleSorter.hpp"
#include "../../sorts/sorters/CocktailSorter/CocktailSorter.hpp"
#include "../../sorts/sorters/CombSorter/CombSorter.hpp"
#include "../../sorts/sorters/CountingSorter/CountingSorter.hpp"
#include "../../sorts/sorters/CycleSorter/CycleSorter.hpp"
#include "../../sorts/sorters/GnomeSorter/GnomeSorter.hpp"
#include "../../sorts/sorters/HeapSorter/HeapSorter.hpp"
#include "../../sorts/sorters/InsertionSorter/InsertionSorter.hpp"
#include "../../sorts/sorters/IterativeMergeSorter/IterativeMergeSorter.hpp"
#include "../../sorts/sorters/IterativeQuickSorter/IterativeQuickSorter.hpp"
#include "../../sorts/sorters/MergeSorter/MergeSorter.hpp"
#include "../../sorts/sorters/OddEvenSorter/OddEvenSorter.hpp"
#include "../../sorts/sorters/QuickSorter/QuickSorter.hpp"
#include "../../sorts/sorters/RadixSorter/RadixSorter.hpp"
#include "../../sorts/sorters/SelectionSorter/SelectionSorter.hpp"
#include "../../sorts/sorters/ShellSorter/ShellSorter.hpp"
#include "../../sorts/sorters/StoogeSorter/StoogeSorter.hpp"

class Sketch {
  SDL_Renderer *renderer_;
  int window_width_ = 0;
  int window_height_ = 0;

  std::string sort_algorithm_ = "bubble";
  void init_sorter_() noexcept;

  bool is_setup_ = false;

  float vertical_scale_ = 0.0f;
  float horizontal_scale_ = 0.0f;
  void calculate_scales_() noexcept;

  u_int32_t steps_per_second_ = 0;
  u_int32_t milliseconds_since_last_sort_ = 0;

  std::size_t seq_len_ = 0;
  std::size_t max_value_ = 0;
  kogan::SharedPtr<kogan::SmartPtrSequence<int>> sequence_;

  kogan::UniquePtr<kogan::Sorter<int>> sorter_;
  bool sorted_drawn_ = false;

  bool reverse_input_ = false;
  void generate_sequence_(uint32_t available_steps) noexcept;
  int sequence_generation_index_ = 0;

  void draw_value_(int index, bool sorted = false, bool interesting = false) const noexcept;

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
  void set_steps_per_second(const u_int32_t &steps_per_second) noexcept;
  void set_sequence_length(const std::size_t &seq_len) noexcept;
  void set_reverse_input(const bool &reverse_input) noexcept;
};