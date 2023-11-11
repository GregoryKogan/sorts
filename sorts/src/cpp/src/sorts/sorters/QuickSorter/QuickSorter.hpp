#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class QuickSorter : public Sorter<T> {
private:
  void set_range_(int l, int h) noexcept;
  bool partition_();

  bool child_sorters_initialized_ = false;
  UniquePtr<QuickSorter<T>> left_sorter_;
  UniquePtr<QuickSorter<T>> right_sorter_;

  bool is_partitioning_ = false;
  bool is_done_ = false;
  int l_ = -1;
  int h_ = -1;
  int p_ = 0;
  int i_ = 0;
  int j_ = 0;

  u_int32_t partition_comparisons_ = 0;
  u_int32_t partition_swaps_ = 0;

  SmartPtrLinkedListSequence<std::size_t>
  generate_interesting_indexes_() const noexcept;

public:
  QuickSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence)
      : Sorter<T>(cmp, sequence) {}

  void sort_() override;

  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "QuickSorter.tpp"