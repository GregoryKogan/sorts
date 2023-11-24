#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class Heapifier;

template <class T> class HeapSorter : public Sorter<T> {
  friend class Heapifier<T>;

private:
  bool initial_heapify_done_;
  bool extracting_started_;
  bool extracting_swap_done_;
  int i_;
  int j_;
  UniquePtr<Heapifier<T>> heapifier_;

public:
  HeapSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    initial_heapify_done_ = false;
    extracting_started_ = false;
    extracting_swap_done_ = false;

    i_ = sequence->get_length() / 2 - 1;
    j_ = sequence->get_length() - 1;

    heapifier_ = make_unique<Heapifier<T>>(this, i_, this->sequence_->get_length());
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

template <class T> class Heapifier {
public:
  Heapifier(HeapSorter<T> *sorter, int index, int heap_size) : sorter_(sorter), index_(index), heap_size_(heap_size) {
    left_checked_ = false;
    right_checked_ = false;
    largest_swap_done_ = false;
    child_heapifier_initialized_ = false;
    largest_ = index_;
    l_ = 2 * index_ + 1;
    r_ = 2 * index_ + 2;
    is_done_ = false;
  }

  void heapify();

  bool is_done() const noexcept { return is_done_; }
  SmartPtrLinkedListSequence<std::size_t> generate_interesting_indexes() const noexcept;

private:
  HeapSorter<T> *sorter_;
  UniquePtr<Heapifier<T>> child_heapifier_;
  bool left_checked_;
  bool right_checked_;
  bool largest_swap_done_;
  bool child_heapifier_initialized_;
  int index_;
  int heap_size_;
  int largest_;
  int l_;
  int r_;
  bool is_done_;
};

} // namespace kogan

#include "HeapSorter.tpp"