#include "IterativeQuickSorter.hpp"

namespace kogan {

template <class T>
inline void IterativeQuickSorter<T>::sort_() {
    auto n = this->sequence_->get_length();

    if (stack_.get_length() < n) {
        stack_.clear();
        for (std::size_t i = 0; i < n; ++i) stack_.append(0);
        top_ = -1;
        stack_[++top_] = 0;
        stack_[++top_] = n - 1;
    }

    while (top_ >= 0 || is_partitioning_) {
        if (!is_partitioning_) {
            h_ = stack_[top_--];
            l_ = stack_[top_--];
        }

        if (!partition_()) return;
        is_partitioning_ = false;

        if (p_ - 1 > l_) {
            stack_[++top_] = l_;
            stack_[++top_] = p_ - 1;
        }

        if (p_ + 1 < h_) {
            stack_[++top_] = p_ + 1;
            stack_[++top_] = h_;
        }
    }
}

template <class T>
inline bool IterativeQuickSorter<T>::partition_() {
    if (!is_partitioning_) {
        is_partitioning_ = true;
        i_ = l_ - 1;
        j_ = l_;
    }

    auto x = this->sequence_->get(h_);

    while (j_ <= h_ - 1) {
        std::optional<int> cmp = this->cmp_wrapper_(this->sequence_->get(j_), x);
        if (!cmp) return false;
        if (cmp.value() <= 0) {
            ++i_;
            if (!this->swap_(i_, j_)) return false;
        }

        ++j_;
    }

    if (!this->swap_(i_ + 1, h_)) return false;
    p_ = i_ + 1;

    return true;
}

template <class T>
inline void IterativeQuickSorter<T>::set_interesting_indexes_() noexcept {
    auto n = this->sequence_->get_length();
    this->interesting_indexes_->clear();
    if (l_ >= 0 && l_ < n) this->interesting_indexes_->append(l_);
    if (h_ >= 0 && h_ < n) this->interesting_indexes_->append(h_);
    if (i_ >= 0 && i_ < n) this->interesting_indexes_->append(i_);
    if (j_ >= 0 && j_ < n) this->interesting_indexes_->append(j_);
}

}  // namespace kogan