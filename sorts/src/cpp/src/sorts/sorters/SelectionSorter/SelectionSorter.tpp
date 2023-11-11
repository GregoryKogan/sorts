#include "SelectionSorter.hpp"

namespace kogan {

template <class T> inline void SelectionSorter<T>::sort_() {
  std::size_t length = this->sequence_->get_length();

  while (i_ < length - 1) {
    while (j_ < length) {
      std::optional<int> cmp = this->cmp_wrapper_(
          this->sequence_->get(min_index_), this->sequence_->get(j_));
      if (!cmp)
        return;
      if (cmp.value() > 0)
        min_index_ = j_;
      ++j_;
    }
    if (!this->swap_(i_, min_index_))
      return;
    ++i_;
    j_ = i_ + 1;
    min_index_ = i_;
  }
}

template <class T>
inline void SelectionSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->clear();
  this->interesting_indexes_->append(i_);
  this->interesting_indexes_->append(j_);
  this->interesting_indexes_->append(min_index_);
}

} // namespace kogan