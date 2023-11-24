#include "IterativeMergeSorter.hpp"

namespace kogan {

template <class T> inline void IterativeMergeSorter<T>::sort_() {
  int n = (int)this->sequence_->get_length();

  while (curr_size_ <= n - 1) {
    while (left_ < n - 1) {
      middle_ = std::min(left_ + curr_size_ - 1, n - 1);
      right_ = std::min(left_ + 2 * curr_size_ - 1, n - 1);

      if (!merge_()) return;
      is_merging_ = false;

      left_ += 2 * curr_size_;
    }
    left_ = 0;
    curr_size_ *= 2;
  }
}

template <class T> inline bool IterativeMergeSorter<T>::merge_() {
  int left_length = middle_ - left_ + 1;
  int right_length = right_ - middle_;

  if (!is_merging_) {
    left_part_.clear();
    right_part_.clear();

    i_ = 0;
    j_ = 0;
    k_ = left_;
  }
  is_merging_ = true;

  if (!buffers_filled_) {
    while (i_ < left_length) {
      if (!this->step_()) return false;

      left_part_.append(this->sequence_->get(left_ + i_));
      ++i_;
    }
    while (j_ < right_length) {
      if (!this->step_()) return false;

      right_part_.append(this->sequence_->get(middle_ + 1 + j_));
      ++j_;
    }

    i_ = 0;
    j_ = 0;
    buffers_filled_ = true;
  }

  while (i_ < left_length && j_ < right_length) {
    if (!this->step_()) return false;

    if (this->cmp_wrapper_(left_part_[i_], right_part_[j_]) <= 0) {
      this->sequence_->set(k_, left_part_[i_]);
      ++i_;
    } else {
      this->sequence_->set(k_, right_part_[j_]);
      ++j_;
    }
    ++k_;
  }

  while (i_ < left_length) {
    if (!this->step_()) return false;
    this->sequence_->set(k_, left_part_[i_]);
    ++i_;
    ++k_;
  }
  while (j_ < right_length) {
    if (!this->step_()) return false;
    this->sequence_->set(k_, right_part_[j_]);
    ++j_;
    ++k_;
  }

  buffers_filled_ = false;
  return true;
}

template <class T> inline void IterativeMergeSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->append(left_);
  this->interesting_indexes_->append(right_);
  this->interesting_indexes_->append(middle_);
  this->interesting_indexes_->append(left_ + i_);
  this->interesting_indexes_->append(middle_ + 1 + j_);
}

} // namespace kogan