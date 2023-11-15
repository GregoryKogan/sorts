#include "QuickSorter.hpp"

namespace kogan {

template <class T> inline void QuickSorter<T>::sort_() {
  if (l_ == -1 && h_ == -1) set_range_(0, this->sequence_->get_length() - 1);

  if (l_ >= h_) {
    is_done_ = true;
    return;
  }

  if (!child_sorters_initialized_) {
    if (!partition_()) return;
    partition_comparisons_ = this->get_comparisons();
    partition_swaps_ = this->get_swaps();
    is_partitioning_ = false;

    left_sorter_ = make_unique<QuickSorter<T>>(this->cmp_, this->sequence_);
    right_sorter_ = make_unique<QuickSorter<T>>(this->cmp_, this->sequence_);

    if (this->is_limited()) {
      left_sorter_->make_limited();
      right_sorter_->make_limited();
    }

    left_sorter_->set_range_(l_, p_ - 1);
    right_sorter_->set_range_(p_ + 1, h_);

    child_sorters_initialized_ = true;
  }

  if (!left_sorter_->is_done_) {
    left_sorter_->add_available_steps(this->get_available_steps());
    left_sorter_->sort_();
    this->available_steps_ = left_sorter_->get_available_steps();
  }

  if (!right_sorter_->is_done_) {
    right_sorter_->add_available_steps(this->get_available_steps());
    right_sorter_->sort_();
    this->available_steps_ = right_sorter_->get_available_steps();
  }

  this->comparisons_ = partition_comparisons_ +
                       left_sorter_->get_comparisons() +
                       right_sorter_->get_comparisons();
  this->swaps_ =
      partition_swaps_ + left_sorter_->get_swaps() + right_sorter_->get_swaps();

  if (left_sorter_->is_done_ && right_sorter_->is_done_) {
    is_done_ = true;
    return;
  }
}

template <class T>
inline void QuickSorter<T>::set_range_(int l, int h) noexcept {
  l_ = l;
  h_ = h;
}

template <class T> inline bool QuickSorter<T>::partition_() {
  if (!is_partitioning_) {
    is_partitioning_ = true;
    i_ = l_ - 1;
    j_ = l_;
  }

  auto x = this->sequence_->get(h_);

  while (j_ <= h_ - 1) {
    if (!this->step_()) return false;

    if (this->cmp_wrapper_(this->sequence_->get(j_), x) <= 0) {
      ++i_;
      this->swap_(i_, j_);
    }

    ++j_;
  }

  this->swap_(i_ + 1, h_);
  p_ = i_ + 1;

  return true;
}

template <class T>
inline SmartPtrLinkedListSequence<std::size_t>
QuickSorter<T>::generate_interesting_indexes_() const noexcept {
  SmartPtrLinkedListSequence<std::size_t> interesting_indexes;

  if (child_sorters_initialized_) {
    auto left_indexes = left_sorter_->generate_interesting_indexes_();
    auto right_indexes = right_sorter_->generate_interesting_indexes_();
    for (std::size_t i = 0; i < left_indexes.get_length(); ++i)
      interesting_indexes.append(left_indexes[i]);
    for (std::size_t i = 0; i < right_indexes.get_length(); ++i)
      interesting_indexes.append(right_indexes[i]);
  }

  if (!is_partitioning_) return interesting_indexes;

  interesting_indexes.append(i_);
  interesting_indexes.append(j_);
  return interesting_indexes;
}

template <class T>
inline void QuickSorter<T>::set_interesting_indexes_() noexcept {
  auto indexes = generate_interesting_indexes_();
  for (std::size_t i = 0; i < indexes.get_length(); ++i)
    this->interesting_indexes_->append(indexes[i]);
}

} // namespace kogan