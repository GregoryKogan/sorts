#ifndef BASE_SORTER_HH
#define BASE_SORTER_HH

#include "BaseSorter.hpp"

namespace kogan {

template <class T>
inline Sorter<T>::Sorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : cmp_(cmp), sequence_(sequence) {}

template <class T>
inline bool Sorter<T>::is_sorted() const noexcept {
    for (std::size_t i = 0; i < sequence_->get_length() - 1; ++i) {
        if (cmp_(sequence_->get(i), sequence_->get(i + 1)) > 0) return false;
    }
    return true;
}

template <class T>
inline u_int32_t Sorter<T>::get_comparisons() const noexcept {
    return comparisons_;
}

template <class T>
inline u_int32_t Sorter<T>::get_swaps() const noexcept {
    return swaps_;
}

template <class T>
inline u_int32_t Sorter<T>::get_available_comparisons() const noexcept {
    return available_comparisons_;
}

template <class T>
inline u_int32_t Sorter<T>::get_available_swaps() const noexcept {
    return available_swaps_;
}

template <class T>
inline bool Sorter<T>::is_limited_in_comparisons() const noexcept {
    return limited_in_comparisons_;
}

template <class T>
inline bool Sorter<T>::is_limited_in_swaps() const noexcept {
    return limited_in_swaps_;
}

template <class T>
inline void Sorter<T>::add_available_comparisons(u_int32_t available_comparisons) noexcept {
    available_comparisons_ += available_comparisons;
}

template <class T>
inline void Sorter<T>::add_available_swaps(u_int32_t available_swaps) noexcept {
    available_swaps_ += available_swaps;
}

template <class T>
inline void Sorter<T>::make_limited_in_comparisons() noexcept {
    limited_in_comparisons_ = true;
    available_comparisons_ = 0;
}

template <class T>
inline void Sorter<T>::make_limited_in_swaps() noexcept {
    limited_in_swaps_ = true;
    available_swaps_ = 0;
}

template <class T>
inline void Sorter<T>::make_unlimited_in_comparisons() noexcept {
    limited_in_comparisons_ = false;
    available_comparisons_ = 0;
}

template <class T>
inline void Sorter<T>::make_unlimited_in_swaps() noexcept {
    limited_in_swaps_ = false;
    available_swaps_ = 0;
}

template <class T>
inline void Sorter<T>::sort() {
    try {
        sort_();
    } catch (OutOfComparisonsException& e) {
        return;
    } catch (OutOfSwapsException& e) {
        return;
    }
}

template <class T>
inline int Sorter<T>::cmp_wrapper_(T a, T b) {
    if (limited_in_comparisons_ && !available_comparisons_) throw OutOfComparisonsException();
    if (limited_in_comparisons_) --available_comparisons_;

    ++comparisons_;
    return cmp_(a, b);
}

template <class T>
inline void Sorter<T>::swap_(int i, int j) {
    if (limited_in_swaps_ && !available_swaps_) throw OutOfSwapsException();
    if (limited_in_swaps_) --available_swaps_;

    ++swaps_;
    T tmp = sequence_->get(i);
    sequence_->set(i, sequence_->get(j));
    sequence_->set(j, tmp);
}

}  // namespace kogan

#endif