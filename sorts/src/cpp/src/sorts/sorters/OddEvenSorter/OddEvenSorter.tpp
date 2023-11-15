#include "OddEvenSorter.hpp"

namespace kogan {

template <class T> inline void OddEvenSorter<T>::sort_() {
  if (finished_) return;

  while (true) {
    if (index_ % 2 == 1) {
      while (index_ <= this->sequence_->get_length() - 2) {
        if (!this->step_()) return;
        if (this->cmp_wrapper_(this->sequence_->get(index_), this->sequence_->get(index_ + 1)) > 0) {
          this->swap_(index_, index_ + 1);
          swapped_ = true;
        }
        index_ += 2;
      }
      index_ = 0;
    }

    while (index_ <= this->sequence_->get_length() - 2) {
      if (!this->step_()) return;
      if (this->cmp_wrapper_(this->sequence_->get(index_), this->sequence_->get(index_ + 1)) > 0) {
        this->swap_(index_, index_ + 1);
        swapped_ = true;
      }
      index_ += 2;
    }
    index_ = 1;

    if (!swapped_) {
      finished_ = true;
      break;
    }
    swapped_ = false;
  }
}

template <class T> inline void OddEvenSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->append(index_);
}

} // namespace kogan