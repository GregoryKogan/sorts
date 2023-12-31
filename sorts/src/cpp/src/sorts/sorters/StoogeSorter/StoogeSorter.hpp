#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class StoogeSorter : public Sorter<T> {
  int l_;
  int r_;
  bool ends_checked_;
  bool finished_;

  UniquePtr<StoogeSorter<T>> first_sorter_;
  UniquePtr<StoogeSorter<T>> second_sorter_;
  UniquePtr<StoogeSorter<T>> third_sorter_;

  void set_range_(int l, int r);
  SmartPtrArraySequence<std::size_t> generate_interesting_indexes_() const noexcept;

public:
  StoogeSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    l_ = -1;
    r_ = -1;
    ends_checked_ = false;
    finished_ = false;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "StoogeSorter.tpp"