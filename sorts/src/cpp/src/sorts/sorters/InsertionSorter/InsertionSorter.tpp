#include "InsertionSorter.hpp"

namespace kogan {

template <class T> inline void InsertionSorter<T>::sort_() {
  std::size_t length = this->sequence_->get_length();

  while (i_ < length) {
    if (j_ == 0) {
      ++i_;
      j_ = i_;
      continue;
    }

    if (!this->step_()) return;

    if (this->cmp_wrapper_(this->sequence_->get(j_),
                           this->sequence_->get(j_ - 1)) < 0) {
      this->swap_(j_, j_ - 1);
      --j_;
    } else {
      ++i_;
      j_ = i_;
    }
  }
}

template <class T>
inline void InsertionSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->clear();
  this->interesting_indexes_->append(j_);
  this->interesting_indexes_->append(i_);
}

} // namespace kogan