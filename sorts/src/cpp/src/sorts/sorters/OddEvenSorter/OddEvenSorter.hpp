#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class OddEvenSorter : public Sorter<T> {
  bool swapped_ = false;
  bool finished_ = false;
  int index_ = 1;

public:
  OddEvenSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {}

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "OddEvenSorter.tpp"