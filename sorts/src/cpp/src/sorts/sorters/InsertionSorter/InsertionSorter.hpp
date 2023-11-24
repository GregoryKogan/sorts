#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class InsertionSorter : public Sorter<T> {
private:
  int i_;
  int j_;

public:
  InsertionSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    i_ = 1;
    j_ = 1;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "InsertionSorter.tpp"