#pragma once

#include "../../../../libs/exception_lib/exceptions/EmptyContainerException/EmptyContainerException.hpp"
#include "../../../../libs/exception_lib/exceptions/IndexOutOfRangeException/IndexOutOfRangeException.hpp"
#include "../../smart_pointers/SharedPtr/SharedPtr.hpp"
#include "../../smart_pointers/WeakPtr/WeakPtr.hpp"

namespace kogan {

template <class T> class SmartPtrLinkedList {
private:
  typedef struct Node {
    T data;
    SharedPtr<Node> next;
    WeakPtr<Node> prev;
  } Node;

  typedef struct Root {
    SharedPtr<Node> head;
    SharedPtr<Node> tail;
  } Root;

  SharedPtr<Root> root_;
  std::size_t length_;

public:
  SmartPtrLinkedList();
  SmartPtrLinkedList(SharedPtr<T[]> data, int length);
  SmartPtrLinkedList(const SmartPtrLinkedList<T> &other);

  T get(int index) const;
  T get_first() const;
  T get_last() const;
  [[nodiscard]] std::size_t get_length() const noexcept;

  void set(int index, T value);
  void append(T value) noexcept;
  void prepend(T value) noexcept;
  void insert(int index, T value);
  void remove(int index);
  void clear() noexcept;

  SmartPtrLinkedList<T> get_sublist(int start_index, int end_index) const;
  SmartPtrLinkedList<T>
  concat(const SmartPtrLinkedList<T> &other) const noexcept;

  T &operator[](int index);

  SmartPtrLinkedList &operator=(const SmartPtrLinkedList &other) noexcept {
    if (this != &other) {
      clear();
      init_();
      for (std::size_t i = 0; i < other.length_; ++i)
        append(other.get(i));
    }
    return *this;
  }

private:
  void init_();
  SharedPtr<Node> get_node_(int index) const;
};

} // namespace kogan

#include "SmartPtrLinkedList.tpp"