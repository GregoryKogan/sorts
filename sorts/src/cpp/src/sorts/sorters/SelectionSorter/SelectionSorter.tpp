#include "SelectionSorter.hpp"

namespace kogan {

template <class T> inline void SelectionSorter<T>::sort_() {
  std::size_t length = this->sequence_->get_length();

  while (i_ < length - 1) {
    while (j_ < length) {
      if (!this->step_()) return;

      if (this->cmp_wrapper_(this->sequence_->get(min_index_),
                             this->sequence_->get(j_)) > 0)
        min_index_ = j_;
      ++j_;
    }
    this->swap_(i_, min_index_);
    ++i_;
    j_ = i_ + 1;
    min_index_ = i_;
  }
}

template <class T>
inline void SelectionSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->append(i_);
  this->interesting_indexes_->append(j_);
  this->interesting_indexes_->append(min_index_);
}

} // namespace kogan