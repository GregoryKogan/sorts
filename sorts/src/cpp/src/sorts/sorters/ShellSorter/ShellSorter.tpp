#include "ShellSorter.hpp"

namespace kogan {

template <class T> inline void ShellSorter<T>::sort_() {
  while (gap_ > 0) {
    while (i_ < this->sequence_->get_length()) {
      if (!temp_set_) {
        temp_ = this->sequence_->get(i_);
        temp_set_ = true;
      }
      while (j_ >= gap_ && this->cmp_wrapper_(this->sequence_->get(j_ - gap_), temp_) > 0) {
        if (!this->step_()) return;

        this->sequence_->set(j_, this->sequence_->get(j_ - gap_));
        j_ -= gap_;
      }
      this->sequence_->set(j_, temp_);
      i_++;
      j_ = i_;
      temp_set_ = false;
    }
    gap_ /= 2;
    i_ = gap_;
    j_ = i_;
  }
}

template <class T> inline void ShellSorter<T>::set_interesting_indexes_() noexcept {
  if (!gap_ || this->sequence_->get_length() / gap_ > 128) {
    this->interesting_indexes_->append(i_);
    return;
  }

  int ind = i_;
  while (ind >= 0) {
    this->interesting_indexes_->append(ind);
    ind -= gap_;
  }
}

} // namespace kogan