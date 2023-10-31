#ifndef SELECTION_SORTER_HH
#define SELECTION_SORTER_HH

#include "SelectionSorter.hpp"

namespace kogan {

template <class T>
inline void SelectionSorter<T>::sort_() {
    for (; i_ < this->sequence_->get_length() - 1; ++i_) {
        min_index_ = i_;
        for (; j_ < this->sequence_->get_length(); ++j_) {
            if (this->cmp_wrapper_(this->sequence_->get(j_), this->sequence_->get(min_index_)) < 0) {
                min_index_ = j_;
            }
        }
        j_ = i_ + 1;

        if (min_index_ != i_) this->swap_(i_, min_index_);
    }
    i_ = 0;
}

}  // namespace kogan

#endif