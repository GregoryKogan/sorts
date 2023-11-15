#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class IterativeQuickSorter : public Sorter<T> {
private:
  bool partition_();
  bool is_partitioning_ = false;

  SmartPtrArraySequence<int> stack_;
  int l_ = 0;
  int h_ = 0;
  int p_ = 0;
  int top_ = 0;
  int i_ = 0;
  int j_ = 0;

public:
  IterativeQuickSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {}

  void sort_() override;

  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "IterativeQuickSorter.tpp"