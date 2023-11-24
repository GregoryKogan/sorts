#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class IterativeQuickSorter : public Sorter<T> {
private:
  bool partition_();
  bool is_partitioning_;

  SmartPtrArraySequence<int> stack_;
  int l_;
  int h_;
  int p_;
  int top_;
  int i_;
  int j_;

public:
  IterativeQuickSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    is_partitioning_ = false;
    l_ = 0;
    h_ = 0;
    p_ = 0;
    top_ = 0;
    i_ = 0;
    j_ = 0;
  }

  void sort_() override;

  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "IterativeQuickSorter.tpp"