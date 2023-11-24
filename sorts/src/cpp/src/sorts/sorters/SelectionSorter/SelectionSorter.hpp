#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class SelectionSorter : public Sorter<T> {
private:
  int i_;
  int j_;
  int min_index_;

public:
  SelectionSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    i_ = 0;
    j_ = i_ + 1;
    min_index_ = 0;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "SelectionSorter.tpp"