#include "IterativeMergeSorter.hpp"

namespace kogan {

template <class T>
inline void IterativeMergeSorter<T>::sort_() {
    std::size_t n = this->sequence_->get_length();

    while (curr_size_ <= n - 1) {
        while (left_ < n - 1) {
            middle_ = std::min(left_ + curr_size_ - 1, n - 1);
            right_ = std::min(left_ + 2 * curr_size_ - 1, n - 1);

            if (!merge_()) return;
            is_merging_ = false;

            left_ += 2 * curr_size_;
        }
        left_ = 0;
        curr_size_ *= 2;
    }
}

template <class T>
inline bool IterativeMergeSorter<T>::merge_() {
    std::size_t left_length = middle_ - left_ + 1;
    std::size_t right_length = right_ - middle_;

    if (!is_merging_) {
        left_part_.clear();
        right_part_.clear();
        for (std::size_t i = 0; i < left_length; ++i) left_part_.append(this->sequence_->get(left_ + i));
        for (std::size_t i = 0; i < right_length; ++i) right_part_.append(this->sequence_->get(middle_ + 1 + i));

        i_ = 0;
        j_ = 0;
        k_ = left_;
    }
    is_merging_ = true;

    while (i_ < left_length && j_ < right_length) {
        std::optional<int> cmp = this->cmp_wrapper_(left_part_[i_], right_part_[j_]);
        if (!cmp) return false;
        if (cmp.value() <= 0) {
            this->sequence_->set(k_, left_part_[i_]);
            ++i_;
        } else {
            this->sequence_->set(k_, right_part_[j_]);
            ++j_;
        }
        ++k_;
    }

    while (i_ < left_length) {
        this->sequence_->set(k_, left_part_[i_]);
        ++i_;
        ++k_;
    }
    while (j_ < right_length) {
        this->sequence_->set(k_, right_part_[j_]);
        ++j_;
        ++k_;
    }

    return true;
}

template <class T>
inline void IterativeMergeSorter<T>::set_interesting_indexes_() noexcept {
    this->interesting_indexes_->clear();
    this->interesting_indexes_->append(left_);
    this->interesting_indexes_->append(right_);
    this->interesting_indexes_->append(middle_);
    this->interesting_indexes_->append(left_ + i_);
    this->interesting_indexes_->append(middle_ + 1 + j_);
}

}  // namespace kogan