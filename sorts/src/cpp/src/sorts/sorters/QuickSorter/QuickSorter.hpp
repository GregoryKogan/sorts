#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class QuickSorter : public Sorter<T> {
  void set_range_(int l, int h) noexcept;
  bool partition_();

  bool child_sorters_initialized_;
  UniquePtr<QuickSorter<T>> left_sorter_;
  UniquePtr<QuickSorter<T>> right_sorter_;

  bool is_partitioning_;
  bool is_done_;
  int l_;
  int h_;
  int p_;
  int i_;
  int j_;

  u_int32_t partition_comparisons_ = 0;
  u_int32_t partition_swaps_ = 0;

  SmartPtrLinkedListSequence<std::size_t> generate_interesting_indexes_() const noexcept;

public:
  QuickSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    child_sorters_initialized_ = false;
    is_partitioning_ = false;
    is_done_ = false;
    l_ = -1;
    h_ = -1;
    p_ = 0;
    i_ = 0;
    j_ = 0;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "QuickSorter.tpp"