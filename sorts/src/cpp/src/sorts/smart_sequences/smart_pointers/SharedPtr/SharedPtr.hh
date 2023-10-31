#ifndef LAB1_SHARED_PTR_HH
#define LAB1_SHARED_PTR_HH

#include "SharedPtr.hpp"

namespace kogan {

/* std::enable_if is a type trait used to enable or disable function templates based on the properties of their template
 * arguments. std::is_array is a type trait used to determine if a type is an array. std::remove_extent is a type trait
 * used to remove the extent (i.e., the array size) from an array type. std::forward is a utility function used to
 * forward arguments to another function. */

template <class T, class... Args>
typename std::enable_if<!std::is_array<T>::value, SharedPtr<T>>::type make_shared(
    Args&&... args) {  // make_shared for non-array types
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
typename std::enable_if<std::is_array<T>::value, SharedPtr<T>>::type make_shared(
    std::size_t size) {  // make_shared for array types
    return SharedPtr<T>(new typename std::remove_extent<T>::type[size]());
}

template <class T>
inline void SharedPtr<T>::update_reference(ControlBlock<T>* new_control_block) {
    if (control_block_) control_block_->decrement_reference_counter_and_delete_if_zero();
    control_block_ = new_control_block;
}

template <class T>
inline void SharedPtr<T[]>::update_reference(ControlBlock<T[]>* new_control_block) {
    if (control_block_) control_block_->decrement_reference_counter_and_delete_if_zero();
    control_block_ = new_control_block;
}

template <class T>
inline SharedPtr<T>::SharedPtr() noexcept {  // default constructor
    control_block_ = nullptr;
}

template <class T>
inline SharedPtr<T[]>::SharedPtr() noexcept {  // default constructor for arrays
    control_block_ = nullptr;
}

template <class T>
inline SharedPtr<T>::SharedPtr(T* ptr) noexcept {  // constructor from pointer
    control_block_ = new ControlBlock<T>(ptr);
}

template <class T>
inline SharedPtr<T[]>::SharedPtr(T* ptr) noexcept {  // constructor from pointer for arrays
    control_block_ = new ControlBlock<T[]>(ptr);
}

template <class T>
inline SharedPtr<T>::SharedPtr(const SharedPtr& other) noexcept
    : control_block_(other.control_block_) {  // copy constructor
    if (control_block_ && control_block_->get() != nullptr) control_block_->increment_reference_counter();
}

template <class T>
inline SharedPtr<T[]>::SharedPtr(const SharedPtr& other) noexcept
    : control_block_(other.control_block_) {  // copy constructor for arrays
    if (control_block_ && control_block_->get() != nullptr) control_block_->increment_reference_counter();
}

template <class T>
inline SharedPtr<T>::SharedPtr(const WeakPtr<T>& other) {  // constructor from WeakPtr
    if (other.expired()) throw EmptyPointerException();
    control_block_ = other.control_block_;
    if (control_block_ && control_block_->get() != nullptr) control_block_->increment_reference_counter();
}

template <class T>
inline SharedPtr<T[]>::SharedPtr(const WeakPtr<T[]>& other) {  // constructor from WeakPtr for arrays
    if (other.expired()) throw EmptyPointerException();
    control_block_ = other.control_block_;
    if (control_block_ && control_block_->get() != nullptr) control_block_->increment_reference_counter();
}

template <class T>
inline SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept : control_block_(other.control_block_) {  // move constructor
    other.control_block_ = nullptr;
}

template <class T>
inline SharedPtr<T[]>::SharedPtr(SharedPtr&& other) noexcept
    : control_block_(other.control_block_) {  // move constructor for arrays
    other.control_block_ = nullptr;
}

template <class T>
inline SharedPtr<T>::~SharedPtr() {
    update_reference(nullptr);
}

template <class T>
inline SharedPtr<T[]>::~SharedPtr() {
    update_reference(nullptr);
}

template <class T>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) noexcept {  // copy assignment
    if (this != &other) {
        update_reference(other.control_block_);
        if (control_block_ && control_block_->get() != nullptr) control_block_->increment_reference_counter();
    }
    return *this;
}

template <class T>
inline SharedPtr<T[]>& SharedPtr<T[]>::operator=(const SharedPtr<T[]>& other) noexcept {  // copy assignment for arrays
    if (this != &other) {
        update_reference(other.control_block_);
        if (control_block_ && control_block_->get() != nullptr) control_block_->increment_reference_counter();
    }
    return *this;
}

template <class T>
inline SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {  // move assignment
    if (this != &other) {
        update_reference(other.control_block_);
        other.control_block_ = nullptr;
    }
    return *this;
}

template <class T>
inline SharedPtr<T[]>& SharedPtr<T[]>::operator=(SharedPtr<T[]>&& other) noexcept {  // move assignment for arrays
    if (this != &other) {
        update_reference(other.control_block_);
        other.control_block_ = nullptr;
    }
    return *this;
}

template <class T>
inline SharedPtr<T>& SharedPtr<T>::operator=(std::nullptr_t) noexcept {  // assignment from nullptr
    update_reference(nullptr);
    return *this;
}

template <class T>
inline SharedPtr<T[]>& SharedPtr<T[]>::operator=(std::nullptr_t) noexcept {  // assignment from nullptr for arrays
    update_reference(nullptr);
    return *this;
}

template <class T>
inline void SharedPtr<T>::reset(T* ptr) noexcept {
    if (ptr != nullptr)
        update_reference(new ControlBlock<T>(ptr));
    else
        update_reference(nullptr);
}

template <class T>
inline void SharedPtr<T[]>::reset(T* ptr) noexcept {
    if (ptr != nullptr)
        update_reference(new ControlBlock<T[]>(ptr));
    else
        update_reference(nullptr);
}

template <class T>
inline void SharedPtr<T>::swap(SharedPtr<T>& other) noexcept {
    std::swap(control_block_, other.control_block_);
}

template <class T>
inline void SharedPtr<T[]>::swap(SharedPtr<T[]>& other) noexcept {
    std::swap(control_block_, other.control_block_);
}

template <class T>
inline bool SharedPtr<T>::unique() const noexcept {
    return use_count() == 1;
}

template <class T>
inline bool SharedPtr<T[]>::unique() const noexcept {
    return use_count() == 1;
}

template <class T>
inline SharedPtr<T>::operator bool() const noexcept {
    return get() != nullptr;
}

template <class T>
inline SharedPtr<T[]>::operator bool() const noexcept {
    return get() != nullptr;
}

template <class T>
inline T* SharedPtr<T>::get() const noexcept {
    if (control_block_ == nullptr) return nullptr;
    return control_block_->get();
}

template <class T>
inline T* SharedPtr<T[]>::get() const noexcept {
    if (control_block_ == nullptr) return nullptr;
    return control_block_->get();
}

template <class T>
inline T* SharedPtr<T>::operator->() const noexcept {
    return get();
}

template <class T>
inline T& SharedPtr<T>::operator*() const noexcept {
    return *(get());
}

template <class T>
inline T& SharedPtr<T[]>::operator[](std::size_t index) const {
    return get()[index];
}

template <class T>
inline unsigned int SharedPtr<T>::use_count() const noexcept {
    if (control_block_ == nullptr) return 0;
    return control_block_->get_reference_counter();
}

template <class T>
inline unsigned int SharedPtr<T[]>::use_count() const noexcept {
    if (control_block_ == nullptr) return 0;
    return control_block_->get_reference_counter();
}

}  // namespace kogan

#endif