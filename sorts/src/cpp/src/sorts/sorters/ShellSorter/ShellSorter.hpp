#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class ShellSorter : public Sorter<T> {
  int gap_;
  T temp_;
  bool temp_set_;
  int i_;
  int j_;

public:
  ShellSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    gap_ = sequence->get_length() / 2;
    temp_set_ = false;
    i_ = gap_;
    j_ = i_;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "ShellSorter.tpp"