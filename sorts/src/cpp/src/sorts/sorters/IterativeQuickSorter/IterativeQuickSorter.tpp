#include "IterativeQuickSorter.hpp"

namespace kogan {

template <class T> inline void IterativeQuickSorter<T>::sort_() {
  auto n = this->sequence_->get_length();

  if (stack_.get_length() < n) {
    stack_.clear();
    for (std::size_t i = 0; i < n; ++i) stack_.append(0);
    top_ = -1;
    stack_[++top_] = 0;
    stack_[++top_] = n - 1;
  }

  while (top_ >= 0 || is_partitioning_) {
    if (!is_partitioning_) {
      h_ = stack_[top_--];
      l_ = stack_[top_--];
    }

    if (!partition_()) return;
    is_partitioning_ = false;

    if (p_ - 1 > l_) {
      stack_[++top_] = l_;
      stack_[++top_] = p_ - 1;
    }

    if (p_ + 1 < h_) {
      stack_[++top_] = p_ + 1;
      stack_[++top_] = h_;
    }
  }
}

template <class T> inline bool IterativeQuickSorter<T>::partition_() {
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

template <class T> inline void IterativeQuickSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->append(l_);
  this->interesting_indexes_->append(h_);
  this->interesting_indexes_->append(i_);
  this->interesting_indexes_->append(j_);
}

} // namespace kogan