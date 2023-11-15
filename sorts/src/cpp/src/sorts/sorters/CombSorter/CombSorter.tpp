#include "CombSorter.hpp"

namespace kogan {

template <class T> inline void CombSorter<T>::sort_() {
  if (finished_) return;

  while (true) {
    while (i_ < this->sequence_->get_length() - gap_) {
      if (!this->step_()) return;

      if (this->cmp_wrapper_(this->sequence_->get(i_), this->sequence_->get(i_ + gap_)) > 0) {
        this->swap_(i_, i_ + gap_);
        swapped_ = true;
      }
      ++i_;
    }
    i_ = 0;
    next_gap_();
    if (!swapped_ && gap_ == 1) {
      finished_ = true;
      break;
    };
    swapped_ = false;
  }
}

template <class T> inline void CombSorter<T>::next_gap_() {
  gap_ = gap_ * 10 / 13;
  if (gap_ < 1) gap_ = 1;
}

template <class T> inline void CombSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->append(i_);
  this->interesting_indexes_->append(i_ + gap_);
}

} // namespace kogan