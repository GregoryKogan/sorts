#ifndef INSERTION_SORTER_HH
#define INSERTION_SORTER_HH

#include "InsertionSorter.hpp"

namespace kogan {

template <class T>
inline void InsertionSorter<T>::sort_() {
    std::size_t length = this->sequence_->get_length();

    while (i_ < length) {
        if (j_ == 0) {
            ++i_;
            j_ = i_;
            continue;
        }
        std::optional<int> cmp = this->cmp_wrapper_(this->sequence_->get(j_), this->sequence_->get(j_ - 1));
        if (!cmp) return;
        if (cmp.value() < 0) {
            if (!this->swap_(j_, j_ - 1)) return;
            --j_;
        } else {
            ++i_;
            j_ = i_;
        }
    }
    i_ = 1;
    j_ = 1;
}

template <class T>
inline void InsertionSorter<T>::set_interesting_indexes_() noexcept {
    this->interesting_indexes_->clear();
    this->interesting_indexes_->append(j_);
    this->interesting_indexes_->append(i_);
}

}  // namespace kogan

#endif