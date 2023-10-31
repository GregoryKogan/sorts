#ifndef LAB1_SMART_PTR_LINKED_LIST_HH
#define LAB1_SMART_PTR_LINKED_LIST_HH

#include "SmartPtrLinkedList.hpp"

namespace kogan {

template <class T>
inline SmartPtrLinkedList<T>::SmartPtrLinkedList() {
    init_();
}

template <class T>
inline SmartPtrLinkedList<T>::SmartPtrLinkedList(SharedPtr<T[]> data, int length) {
    if (length < 0) throw InvalidArgumentException("length must be positive");

    init_();
    for (std::size_t i = 0; i < length; ++i) append(data[i]);
}

template <class T>
inline SmartPtrLinkedList<T>::SmartPtrLinkedList(const SmartPtrLinkedList<T>& other) {
    init_();
    for (std::size_t i = 0; i < other.length_; ++i) append(other.get(i));
}

template <class T>
inline T SmartPtrLinkedList<T>::get(int index) const {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);
    return get_node_(index)->data;
}

template <class T>
inline T SmartPtrLinkedList<T>::get_first() const {
    if (length_ == 0) throw EmptyContainerException();
    return root_->head->data;
}

template <class T>
inline T SmartPtrLinkedList<T>::get_last() const {
    if (length_ == 0) throw EmptyContainerException();
    return root_->tail->data;
}

template <class T>
inline std::size_t SmartPtrLinkedList<T>::get_length() const noexcept {
    return length_;
}

template <class T>
inline void SmartPtrLinkedList<T>::set(int index, T value) {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);
    get_node_(index)->data = value;
}

template <class T>
inline void SmartPtrLinkedList<T>::append(T value) noexcept {
    auto new_node = make_shared<Node>();
    new_node->data = value;
    new_node->prev = root_->tail;
    new_node->next = nullptr;
    if (length_ == 0) {
        root_->head = new_node;
        root_->tail = new_node;
    } else {
        root_->tail->next = new_node;
        root_->tail = new_node;
    }
    ++length_;
}

template <class T>
inline void SmartPtrLinkedList<T>::prepend(T value) noexcept {
    auto new_node = make_shared<Node>();
    new_node->data = value;
    new_node->prev = nullptr;
    new_node->next = root_->head;
    if (length_ == 0) {
        root_->head = new_node;
        root_->tail = new_node;
    } else {
        root_->head->prev = new_node;
        root_->head = new_node;
    }
    ++length_;
}

template <class T>
inline void SmartPtrLinkedList<T>::insert(int index, T value) {
    if (index < 0 || index > length_) throw IndexOutOfRangeException(index, 0, length_);

    if (index == 0) {
        prepend(value);
        return;
    }
    if (index == length_) {
        append(value);
        return;
    }

    auto cur_node = get_node_(index);
    auto new_node = make_shared<Node>();
    new_node->data = value;
    new_node->prev = cur_node->prev;
    new_node->next = cur_node;
    cur_node->prev.lock()->next = new_node;
    cur_node->prev = new_node;
    ++length_;
}

template <class T>
inline void SmartPtrLinkedList<T>::remove(int index) {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);

    if (index == 0) {
        auto new_head = root_->head->next;
        root_->head = new_head;
        if (root_->head != nullptr) root_->head->prev = nullptr;
        --length_;
        return;
    }
    if (index == length_ - 1) {
        root_->tail = root_->tail->prev.lock();
        if (root_->tail != nullptr) root_->tail->next = nullptr;
        --length_;
        return;
    }

    auto cur_node = get_node_(index);
    cur_node->prev.lock()->next = cur_node->next;
    cur_node->next->prev = cur_node->prev;
    --length_;
}

template <class T>
inline void SmartPtrLinkedList<T>::clear() noexcept {
    root_->head = nullptr;
    root_->tail = nullptr;
    length_ = 0;
}

template <class T>
inline SmartPtrLinkedList<T> SmartPtrLinkedList<T>::get_sublist(int start_index, int end_index) const {
    if (start_index < 0 || start_index >= length_) throw IndexOutOfRangeException(start_index, 0, length_ - 1);
    if (end_index < 0 || end_index >= length_) throw IndexOutOfRangeException(end_index, 0, length_ - 1);
    if (start_index > end_index) throw InvalidArgumentException("start_index must be less than or equal to end_index");

    auto new_list = SmartPtrLinkedList<T>();
    for (std::size_t i = start_index; i <= end_index; ++i) new_list.append(get(i));
    return new_list;
}

template <class T>
inline SmartPtrLinkedList<T> SmartPtrLinkedList<T>::concat(const SmartPtrLinkedList<T>& other) const noexcept {
    auto new_list = SmartPtrLinkedList<T>(*this);
    for (std::size_t i = 0; i < other.length_; ++i) new_list.append(other.get(i));
    return new_list;
}

template <class T>
inline T& SmartPtrLinkedList<T>::operator[](int index) {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);
    return get_node_(index)->data;
}

template <class T>
inline void SmartPtrLinkedList<T>::init_() {
    root_ = make_shared<Root>();
    root_->head = nullptr;
    root_->tail = nullptr;
    length_ = 0;
}

template <class T>
inline SharedPtr<typename SmartPtrLinkedList<T>::Node> SmartPtrLinkedList<T>::get_node_(int index) const {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);

    if (index < length_ / 2) {  // search from head
        auto cur_node = root_->head;
        for (std::size_t i = 0; i < index; ++i) cur_node = cur_node->next;
        return cur_node;
    } else {  // search from tail
        auto cur_node = root_->tail;
        for (std::size_t i = length_ - 1; i > index; --i) cur_node = cur_node->prev;
        return cur_node;
    }
}

}  // namespace kogan

#endif