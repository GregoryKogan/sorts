#include "RadixSorter.hpp"

namespace kogan {

inline void RadixSorter::sort_() {
  if (!max_val_found_) {
    if (!find_max_value_()) return;
    max_val_found_ = true;
  }

  while (max_val_ / exp_ > 0) {
    if (!count_sorting_) {
      counting_array_.clear();
      for (int i = 0; i < 10; ++i) counting_array_.append(0);
    }

    if (!count_sort_()) return;
    count_sorting_ = false;
    exp_ *= 10;
  }
}

inline bool kogan::RadixSorter::find_max_value_() {
  while (max_val_search_index_ < this->sequence_->get_length()) {
    if (!this->step_()) return false;

    if (this->cmp_wrapper_(max_val_, this->sequence_->get(max_val_search_index_)) < 0)
      max_val_ = this->sequence_->get(max_val_search_index_);

    ++max_val_search_index_;
    output_array_.append(0);
  }
  return true;
}

inline bool kogan::RadixSorter::count_sort_() {
  count_sorting_ = true;

  if (!output_array_filled_) {
    while (counting_array_index_ < this->sequence_->get_length()) {
      if (!this->step_()) return false;
      counting_array_[(this->sequence_->get(counting_array_index_) / exp_) % 10]++;
      ++counting_array_index_;
    }

    if (output_array_index_ == -2) {
      for (int i = 1; i < 10; i++) counting_array_[i] += counting_array_[i - 1];
      output_array_index_ = this->sequence_->get_length() - 1;
    }
    while (output_array_index_ >= 0) {
      if (!this->step_()) return false;
      output_array_[counting_array_[(this->sequence_->get(output_array_index_) / exp_) % 10] - 1] =
          this->sequence_->get(output_array_index_);
      counting_array_[(this->sequence_->get(output_array_index_) / exp_) % 10]--;
      --output_array_index_;
    }

    output_array_filled_ = true;
  }

  while (i_ < this->sequence_->get_length()) {
    if (!this->step_()) return false;

    this->sequence_->set(i_, output_array_[i_]);
    ++i_;
  }

  i_ = 0;
  output_array_filled_ = false;
  counting_array_index_ = 0;
  output_array_index_ = -2;
  return true;
}

inline void RadixSorter::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->append(max_val_search_index_);
  if (i_ != 0) this->interesting_indexes_->append(i_);
  if (counting_array_index_ != 0) this->interesting_indexes_->append(counting_array_index_);
  this->interesting_indexes_->append(output_array_index_);
}

} // namespace kogan