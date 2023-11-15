#include "Sketch.hpp"

Sketch::Sketch(SDL_Renderer *renderer) : renderer_(renderer) {}

void Sketch::setup() {
  sequence_ = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrArraySequence<int>());
  sequence_generation_index_ = 0;
  sorted_drawn_ = false;
  is_setup_ = true;
}

void Sketch::update(const double &delta_time) {
  if (!is_setup_) return;

  milliseconds_since_last_sort_ += delta_time;
  uint32_t available_steps = milliseconds_since_last_sort_ * steps_per_second_ / 1000;

  if (!available_steps) return;
  milliseconds_since_last_sort_ = 0;

  if (sequence_generation_index_ < seq_len_) {
    generate_sequence_(available_steps);
    return;
  }

  if (sorter_->is_sorted()) return;

  sorter_->add_available_steps(available_steps);
  sorter_->sort();

  if (sorter_->is_sorted()) {
    draw();
    sorted_drawn_ = true;
  }
}

void Sketch::draw() const noexcept {
  if (sorted_drawn_) return;

  SDL_SetRenderDrawColor(renderer_, 36, 40, 59, 255);
  SDL_RenderClear(renderer_);

  if (!is_setup_) {
    SDL_RenderPresent(renderer_);
    return;
  }

  if (sequence_generation_index_ < seq_len_) {
    for (std::size_t i = 0; i < sequence_->get_length(); ++i) draw_value_(i);
    draw_value_(sequence_->get_length() - 1, false, true);
    SDL_RenderPresent(renderer_);
    return;
  }

  for (std::size_t i = 0; i < sequence_->get_length(); ++i) draw_value_(i, sorter_->is_sorted());

  if (!sorter_->is_sorted()) {
    auto interesting_indexes = sorter_->get_interesting_indexes();
    for (std::size_t i = 0; i < interesting_indexes->get_length(); ++i) {
      draw_value_(interesting_indexes->get(i), false, true);
    }
  }

  SDL_RenderPresent(renderer_);
}

void Sketch::set_window_size(const int &width, const int &height) noexcept {
  window_width_ = width;
  window_height_ = height;
  calculate_scales_();
}

u_int32_t Sketch::get_comparisons() const noexcept { return sorter_->get_comparisons(); }

u_int32_t Sketch::get_swaps() const noexcept { return sorter_->get_swaps(); }

void Sketch::set_sort_algorithm(const std::string &algorithm) noexcept { sort_algorithm_ = algorithm; }

void Sketch::set_steps_per_second(const u_int32_t &steps_per_second) noexcept { steps_per_second_ = steps_per_second; }

void Sketch::set_sequence_length(const std::size_t &seq_len) noexcept {
  seq_len_ = seq_len;
  max_value_ = seq_len_;
  calculate_scales_();
}

void Sketch::init_sorter_() noexcept {
  if (sort_algorithm_ == "bubble") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::BubbleSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else if (sort_algorithm_ == "selection") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::SelectionSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else if (sort_algorithm_ == "insertion") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::InsertionSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else if (sort_algorithm_ == "merge") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::MergeSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else if (sort_algorithm_ == "iter_merge") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::IterativeMergeSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else if (sort_algorithm_ == "quick") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::QuickSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else if (sort_algorithm_ == "iter_quick") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::IterativeQuickSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else if (sort_algorithm_ == "heap") {
    sorter_ =
        kogan::UniquePtr<kogan::Sorter<int>>(new kogan::HeapSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else if (sort_algorithm_ == "count") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(new kogan::CountingSorter(sequence_));
  } else if (sort_algorithm_ == "cocktail") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::CocktailSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else if (sort_algorithm_ == "radix") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(new kogan::RadixSorter(sequence_));
  } else if (sort_algorithm_ == "shell") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::ShellSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else if (sort_algorithm_ == "gnome") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::GnomeSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else if (sort_algorithm_ == "odd-even") {
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::OddEvenSorter<int>([](int a, int b) { return a - b; }, sequence_));
  } else { // default to bubble sort if algorithm is not found
    sorter_ = kogan::UniquePtr<kogan::Sorter<int>>(
        new kogan::BubbleSorter<int>([](int a, int b) { return a - b; }, sequence_));
  }
}

void Sketch::calculate_scales_() noexcept {
  horizontal_scale_ = (float)window_width_ / (float)seq_len_;
  vertical_scale_ = (float)(window_height_) / (float)max_value_;
}

void Sketch::generate_sequence_(uint32_t available_steps) noexcept {
  for (int i = 0; i < available_steps && sequence_generation_index_ < seq_len_; ++i) {
    sequence_->append(rand() % max_value_ + 1);
    ++sequence_generation_index_;
  }
  if (sequence_generation_index_ == seq_len_) {
    init_sorter_();
    sorter_->make_limited();
  }
}

void Sketch::draw_value_(int index, bool sorted, bool interesting) const noexcept {
  if (index < 0 || index >= sequence_->get_length()) return;

  SDL_Rect rect;
  rect.x = index * horizontal_scale_;
  rect.y = window_height_ - sequence_->get(index) * vertical_scale_;
  rect.w = std::ceil(horizontal_scale_);
  rect.h = std::ceil(sequence_->get(index) * vertical_scale_);

  if (sorted) {
    SDL_SetRenderDrawColor(renderer_, 158, 206, 106, 255);
  } else if (interesting) {
    SDL_SetRenderDrawColor(renderer_, 247, 118, 142, 255);
    rect.w++;
  } else {
    SDL_SetRenderDrawColor(renderer_, 192, 202, 245, 255);
  }

  SDL_RenderFillRect(renderer_, &rect);
}
