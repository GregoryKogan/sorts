#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class Heapifier;

template <class T> class HeapSorter : public Sorter<T> {
  friend class Heapifier<T>;

private:
  bool started_;
  bool initial_heapify_done_;
  bool extracting_started_;
  bool extracting_swap_done_;
  int i_;
  int j_;
  UniquePtr<Heapifier<T>> heapifier_;

public:
  HeapSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    started_ = false;
    initial_heapify_done_ = false;
    extracting_started_ = false;
    extracting_swap_done_ = false;
    i_ = 0;
    j_ = 0;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

template <class T> class Heapifier {
public:
  Heapifier(HeapSorter<T> *sorter, int index, int heap_size) : sorter_(sorter), index_(index), heap_size_(heap_size) {}

  void heapify();

  bool is_done() const noexcept { return is_done_; }
  SmartPtrLinkedListSequence<std::size_t> generate_interesting_indexes() const noexcept;

private:
  HeapSorter<T> *sorter_;
  UniquePtr<Heapifier<T>> child_heapifier_;
  bool started_ = false;
  bool left_checked_ = false;
  bool right_checked_ = false;
  bool largest_swap_done_ = false;
  bool child_heapifier_initialized_ = false;
  int index_ = 0;
  int heap_size_ = 0;
  int largest_ = 0;
  int l_ = 0;
  int r_ = 0;
  bool is_done_ = false;
};

} // namespace kogan

#include "HeapSorter.tpp"