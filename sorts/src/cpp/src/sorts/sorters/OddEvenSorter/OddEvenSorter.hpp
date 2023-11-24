#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class OddEvenSorter : public Sorter<T> {
  bool swapped_;
  bool finished_;
  int index_;

public:
  OddEvenSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    swapped_ = false;
    finished_ = false;
    index_ = 1;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "OddEvenSorter.tpp"