#ifndef LAB1_SMART_PTR_DYNAMIC_ARRAY_HH
#define LAB1_SMART_PTR_DYNAMIC_ARRAY_HH

#include "SmartPtrDynamicArray.hpp"

namespace kogan {

template <class T>
inline SmartPtrDynamicArray<T>::SmartPtrDynamicArray() {
    length_ = 0;
    data_ = SharedPtr<T[]>();
}

template <class T>
inline SmartPtrDynamicArray<T>::SmartPtrDynamicArray(int length) {
    if (length < 0) throw InvalidArgumentException("length must be positive");
    length_ = length;
    data_ = make_shared<T[]>(length);
}

template <class T>
inline SmartPtrDynamicArray<T>::SmartPtrDynamicArray(SharedPtr<T[]> data, int length) {
    if (length < 0) throw InvalidArgumentException("length must be positive");

    length_ = length;
    data_ = make_shared<T[]>(length_);
    for (std::size_t i = 0; i < length_; ++i) data_[i] = data[i];
}

template <class T>
inline SmartPtrDynamicArray<T>::SmartPtrDynamicArray(const SmartPtrDynamicArray<T>& other) {
    length_ = other.length_;
    data_ = make_shared<T[]>(length_);
    for (std::size_t i = 0; i < length_; ++i) data_[i] = other.data_[i];
}

template <class T>
inline T SmartPtrDynamicArray<T>::get(int index) const {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);
    return data_[index];
}

template <class T>
inline std::size_t SmartPtrDynamicArray<T>::get_length() const noexcept {
    return length_;
}

template <class T>
inline void SmartPtrDynamicArray<T>::set(int index, T value) {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);
    data_[index] = value;
}

template <class T>
inline void SmartPtrDynamicArray<T>::resize(int new_length) {
    if (new_length < 0) throw InvalidArgumentException("length must be positive");
    if (new_length == (int)length_) return;

    SharedPtr<T[]> new_data = make_shared<T[]>(new_length);
    for (std::size_t i = 0; i < std::min((int)length_, new_length); ++i) new_data[i] = data_[i];

    data_ = new_data;
    length_ = new_length;
}

template <class T>
inline T& SmartPtrDynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);

    return data_[index];
}

}  // namespace kogan

#endif