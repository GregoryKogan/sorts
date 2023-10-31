#ifndef LAB1_LINKED_LIST_SEQUENCE_HPP
#define LAB1_LINKED_LIST_SEQUENCE_HPP

#include "../../data_structures/SmartPtrLinkedList/SmartPtrLinkedList.hpp"
#include "../SmartPtrSequence.hpp"

namespace kogan {

template <class T>
class SmartPtrLinkedListSequence : public SmartPtrSequence<T> {
    UniquePtr<SmartPtrLinkedList<T>> list;

   public:
    SmartPtrLinkedListSequence(SharedPtr<T[]> items, int count);
    SmartPtrLinkedListSequence();
    SmartPtrLinkedListSequence(const SmartPtrLinkedListSequence<T> &linkedListSequence);

    T get_first() const override;
    T get_last() const override;
    T get(int index) const override;
    UniquePtr<SmartPtrSequence<T>> get_subsequence(int start_index, int end_index) const override;
    [[nodiscard]] size_t get_length() const override;

    void set(int index, T item) override;
    void append(T item) override;
    void prepend(T item) override;
    void insert(int index, T item) override;
    UniquePtr<SmartPtrSequence<T>> concat(SharedPtr<SmartPtrSequence<T>> sequence) const override;
    void clear() override;
    void remove(int index) override;

    T &operator[](int index) override;
};

}  // namespace kogan

#include "SmartPtrLinkedListSequence.hh"

#endif