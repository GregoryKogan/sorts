#include "BogoSorter.hpp"

namespace kogan {

template <class T> inline void BogoSorter<T>::sort_() {
  while (!sorted_) {
    if (!checked_) {
      if (!check_if_sorted_()) return;
      checked_ = true;
      i_ = 0;
    }

    if (sorted_) return;

    if (!shuffle_()) return;

    checked_ = false;
    i_ = 0;
  }
}

template <class T> inline bool BogoSorter<T>::check_if_sorted_() {
  while (i_ < this->sequence_->get_length() - 1) {
    if (!this->step_()) return false;

    if (this->cmp_wrapper_(this->sequence_->get(i_), this->sequence_->get(i_ + 1)) > 0) {
      sorted_ = false;
      return true;
    }

    ++i_;
  }
  sorted_ = true;
  return true;
}

template <class T> inline bool BogoSorter<T>::shuffle_() {
  while (i_ < this->sequence_->get_length()) {
    if (!this->step_()) return false;

    int j = rand() % this->sequence_->get_length();
    this->swap_(i_, j);

    ++i_;
  }
  return true;
}

template <class T> inline void BogoSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->append(i_);
}

} // namespace kogan