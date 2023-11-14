#include "BubbleSorter.hpp"

namespace kogan {

template <class T> inline void BubbleSorter<T>::sort_() {
  while (i_ < this->sequence_->get_length() - 1) {
    while (j_ < this->sequence_->get_length() - i_ - 1) {
      if (!this->step_())
        return;

      if (this->cmp_wrapper_(this->sequence_->get(j_),
                             this->sequence_->get(j_ + 1)) > 0)
        this->swap_(j_, j_ + 1);

      ++j_;
    }
    j_ = 0;
    ++i_;
  }
}

template <class T>
inline void BubbleSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->clear();
  this->interesting_indexes_->append(j_);
  this->interesting_indexes_->append(this->sequence_->get_length() - i_);
}

} // namespace kogan