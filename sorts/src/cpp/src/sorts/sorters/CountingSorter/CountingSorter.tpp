#include "CountingSorter.hpp"

namespace kogan {

inline void CountingSorter::sort_() {
  std::size_t n = this->sequence_->get_length();

  while (i_ < n) {
    std::optional<int> cmp =
        this->cmp_wrapper_(this->sequence_->get(i_), max_value_);
    if (!cmp)
      return;
    if (cmp.value() > 0)
      max_value_ = this->sequence_->get(i_);
    ++i_;
  }
  max_value_found_ = true;

  counting_array_.clear();
  for (int i = 0; i <= max_value_; ++i)
    counting_array_.append(0);

  output_array_.clear();
  for (std::size_t i = 0; i < n; ++i)
    output_array_.append(0);

  for (std::size_t i = 0; i < n; ++i) {
    int value = this->sequence_->get(i);
    counting_array_[value]++;
  }

  for (int i = 1; i <= max_value_; ++i)
    counting_array_[i] += counting_array_[i - 1];

  for (int i = n - 1; i >= 0; --i) {
    int value = this->sequence_->get(i);
    int index = counting_array_[value] - 1;
    output_array_[index] = value;
    counting_array_[value]--;
  }

  for (std::size_t i = 0; i < n; ++i)
    this->sequence_->set(i, output_array_[i]);
}

inline void CountingSorter::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->clear();
  if (!max_value_found_)
    this->interesting_indexes_->append(i_);
}

} // namespace kogan