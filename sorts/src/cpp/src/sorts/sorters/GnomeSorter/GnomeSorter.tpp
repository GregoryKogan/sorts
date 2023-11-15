#include "GnomeSorter.hpp"

namespace kogan {

template <class T> inline void GnomeSorter<T>::sort_() {
  while (index_ < this->sequence_->get_length()) {
    if (!this->step_()) return;

    if (index_ == 0) ++index_;
    if (this->cmp_wrapper_(this->sequence_->get(index_ - 1),
                           this->sequence_->get(index_)) <= 0)
      ++index_;
    else {
      this->swap_(index_ - 1, index_);
      --index_;
    }
  }
}

template <class T>
inline void GnomeSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->append(index_);
}

} // namespace kogan