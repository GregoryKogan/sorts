#include "RadixSorter.hpp"

namespace kogan {

inline void RadixSorter::sort_() {
  if (!started_) {
    max_val_ = this->sequence_->get(0);
    max_val_search_index_ = 1;
    started_ = true;
  }

  if (!max_val_found_) {
    if (!find_max_value_())
      return;
    max_val_found_ = true;
  }

  while (max_val_ / exp_ > 0) {
    if (!count_sorting_) {
      output_array_.clear();
      for (int i = 0; i < this->sequence_->get_length(); ++i)
        output_array_.append(0);
      counting_array_.clear();
      for (int i = 0; i < 10; ++i)
        counting_array_.append(0);
    }

    if (!count_sort_())
      return;
    count_sorting_ = false;
    exp_ *= 10;
  }
}

inline bool kogan::RadixSorter::find_max_value_() {
  while (max_val_search_index_ < this->sequence_->get_length()) {
    std::optional<int> cmp = this->cmp_wrapper_(
        max_val_, this->sequence_->get(max_val_search_index_));
    if (!cmp)
      return false;
    if (cmp.value() < 0)
      max_val_ = this->sequence_->get(max_val_search_index_);

    ++max_val_search_index_;
  }
  return true;
}

inline bool kogan::RadixSorter::count_sort_() {
  count_sorting_ = true;

  int i;
  for (i = 0; i < this->sequence_->get_length(); i++)
    counting_array_[(this->sequence_->get(i) / exp_) % 10]++;

  for (i = 1; i < 10; i++)
    counting_array_[i] += counting_array_[i - 1];

  for (i = this->sequence_->get_length() - 1; i >= 0; i--) {
    output_array_[counting_array_[(this->sequence_->get(i) / exp_) % 10] - 1] =
        this->sequence_->get(i);
    counting_array_[(this->sequence_->get(i) / exp_) % 10]--;
  }

  for (i = 0; i < this->sequence_->get_length(); i++)
    this->sequence_->set(i, output_array_[i]);

  return true;
}

inline void RadixSorter::set_interesting_indexes_() noexcept {}

} // namespace kogan