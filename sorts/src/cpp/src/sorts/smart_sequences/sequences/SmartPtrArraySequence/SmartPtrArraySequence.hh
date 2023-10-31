#ifndef LAB1_SMART_PTR_ARRAY_SEQUENCE_HH
#define LAB1_SMART_PTR_ARRAY_SEQUENCE_HH

#include "SmartPtrArraySequence.hpp"

namespace kogan {

template <class T>
inline SmartPtrArraySequence<T>::SmartPtrArraySequence(SharedPtr<T[]> items, int count) {
    array = make_unique<SmartPtrDynamicArray<T>>(items, count);
}

template <class T>
SmartPtrArraySequence<T>::SmartPtrArraySequence() {
    array = make_unique<SmartPtrDynamicArray<T>>();
}

template <class T>
SmartPtrArraySequence<T>::SmartPtrArraySequence(const SmartPtrArraySequence<T> &arraySequence) {
    array = make_unique<SmartPtrDynamicArray<T>>(*arraySequence.array);
}

template <class T>
T SmartPtrArraySequence<T>::get_first() const {
    return get(0);
}

template <class T>
T SmartPtrArraySequence<T>::get_last() const {
    return get(get_length() - 1);
}

template <class T>
T SmartPtrArraySequence<T>::get(int index) const {
    return array->get(index);
}

template <class T>
UniquePtr<SmartPtrSequence<T>> SmartPtrArraySequence<T>::get_subsequence(int start_index, int end_index) const {
    if (start_index < 0 || start_index >= get_length())
        throw IndexOutOfRangeException(start_index, 0, get_length() - 1);
    if (end_index < 0 || end_index >= get_length()) throw IndexOutOfRangeException(end_index, 0, get_length() - 1);
    if (end_index < start_index) throw InvalidArgumentException("end_index must be greater than start_index");

    auto sub_seq = UniquePtr<SmartPtrSequence<T>>(new SmartPtrArraySequence<T>());
    for (int i = start_index; i <= end_index; ++i) sub_seq->append(get(i));
    return sub_seq;
}

template <class T>
size_t SmartPtrArraySequence<T>::get_length() const {
    return array->get_length();
}

template <class T>
void SmartPtrArraySequence<T>::set(int index, T item) {
    array->set(index, item);
}

template <class T>
void SmartPtrArraySequence<T>::append(T item) {
    array->resize(get_length() + 1);
    set(get_length() - 1, item);
}

template <class T>
void SmartPtrArraySequence<T>::prepend(T item) {
    array->resize(get_length() + 1);
    for (int i = get_length() - 1; i > 0; --i) set(i, get(i - 1));
    set(0, item);
}

template <class T>
void SmartPtrArraySequence<T>::insert(int index, T item) {
    if (index < 0 || index > get_length()) throw IndexOutOfRangeException(index, 0, get_length());

    if (index == 0)
        prepend(item);
    else if (index == get_length())
        append(item);
    else {
        array->resize(get_length() + 1);
        for (int i = get_length() - 1; i > index; --i) set(i, get(i - 1));
        set(index, item);
    }
}

template <class T>
UniquePtr<SmartPtrSequence<T>> SmartPtrArraySequence<T>::concat(SharedPtr<SmartPtrSequence<T>> sequence) const {
    auto concatenation = UniquePtr<SmartPtrSequence<T>>(new SmartPtrArraySequence<T>(*this));
    for (int i = 0; i < sequence->get_length(); ++i) concatenation->append(sequence->get(i));
    return concatenation;
}

template <class T>
void SmartPtrArraySequence<T>::clear() {
    array->resize(0);
}

template <class T>
void SmartPtrArraySequence<T>::remove(int index) {
    if (index < 0 || index >= get_length()) throw IndexOutOfRangeException(index, 0, get_length() - 1);

    for (int i = index; i < get_length() - 1; ++i) set(i, get(i + 1));
    array->resize(get_length() - 1);
}

template <class T>
T &SmartPtrArraySequence<T>::operator[](int index) {
    return array->operator[](index);
}

}  // namespace kogan

#endif