#ifndef BUBBLE_SORTER_HH
#define BUBBLE_SORTER_HH

#include "BubbleSorter.hpp"

namespace kogan {

template <class T>
inline void BubbleSorter<T>::sort_() {
    for (; i_ < this->sequence_->get_length(); ++i_) {
        for (; j_ < this->sequence_->get_length() - i_ - 1; ++j_) {
            if (this->cmp_wrapper_(this->sequence_->get(j_), this->sequence_->get(j_ + 1)) > 0) {
                this->swap_(j_, j_ + 1);
            }
        }
        j_ = 0;
    }
    i_ = 0;
}

}  // namespace kogan

#endif