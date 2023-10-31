#ifndef LAB1_CONTROL_BLOCK_HH
#define LAB1_CONTROL_BLOCK_HH

#include "ControlBlock.hpp"

namespace kogan {

template <class T>
inline ControlBlock<T>::ControlBlock(T* ptr) {  // constructor from pointer
    if (!ptr) throw InvalidArgumentException("nullptr is not allowed");

    ptr_ = ptr;
    reference_counter_ = 1;
    weak_ptr_reference_counter_ = 0;
}

template <class T>
inline ControlBlock<T[]>::ControlBlock(T* ptr) {  // constructor from pointer for arrays
    if (!ptr) throw InvalidArgumentException("nullptr is not allowed");

    ptr_ = ptr;
    reference_counter_ = 1;
    weak_ptr_reference_counter_ = 0;
}

template <class T>
inline void ControlBlock<T>::increment_reference_counter() noexcept {
    ++reference_counter_;
}

template <class T>
inline void ControlBlock<T[]>::increment_reference_counter() noexcept {
    ++reference_counter_;
}

template <class T>
inline void ControlBlock<T>::decrement_reference_counter_and_delete_if_zero() {
    if (reference_counter_ == 0) throw ZeroReferenceDecrementException();

    if (reference_counter_ == 1 && ptr_ != nullptr) {
        delete ptr_;
        ptr_ = nullptr;
    }
    --reference_counter_;
    if (reference_counter_ + weak_ptr_reference_counter_ == 0) delete this;
}

template <class T>
inline void ControlBlock<T[]>::decrement_reference_counter_and_delete_if_zero() {
    if (reference_counter_ == 0) throw ZeroReferenceDecrementException();

    if (reference_counter_ == 1 && ptr_ != nullptr) {
        delete[] ptr_;
        ptr_ = nullptr;
    }
    --reference_counter_;
    if (reference_counter_ + weak_ptr_reference_counter_ == 0) delete this;
}

template <class T>
inline void ControlBlock<T>::increment_weak_ptr_reference_counter() noexcept {
    ++weak_ptr_reference_counter_;
}

template <class T>
inline void ControlBlock<T[]>::increment_weak_ptr_reference_counter() noexcept {
    ++weak_ptr_reference_counter_;
}

template <class T>
inline void ControlBlock<T>::decrement_weak_ptr_reference_counter_and_delete_if_zero() {
    if (weak_ptr_reference_counter_ == 0) throw ZeroReferenceDecrementException();

    --weak_ptr_reference_counter_;
    if (reference_counter_ + weak_ptr_reference_counter_ == 0) delete this;
}

template <class T>
inline void ControlBlock<T[]>::decrement_weak_ptr_reference_counter_and_delete_if_zero() {
    if (weak_ptr_reference_counter_ == 0) throw ZeroReferenceDecrementException();

    --weak_ptr_reference_counter_;
    if (reference_counter_ + weak_ptr_reference_counter_ == 0) delete this;
}

template <class T>
inline T* ControlBlock<T>::get() const noexcept {
    return ptr_;
}

template <class T>
inline T* ControlBlock<T[]>::get() const noexcept {
    return ptr_;
}

template <class T>
inline unsigned int ControlBlock<T>::get_reference_counter() const noexcept {
    return reference_counter_;
}

template <class T>
inline unsigned int ControlBlock<T[]>::get_reference_counter() const noexcept {
    return reference_counter_;
}

template <class T>
inline unsigned int ControlBlock<T>::get_weak_ptr_reference_counter() const noexcept {
    return weak_ptr_reference_counter_;
}

template <class T>
inline unsigned int ControlBlock<T[]>::get_weak_ptr_reference_counter() const noexcept {
    return weak_ptr_reference_counter_;
}

}  // namespace kogan

#endif