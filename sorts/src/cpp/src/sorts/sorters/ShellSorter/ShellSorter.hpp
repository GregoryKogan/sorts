#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class ShellSorter : public Sorter<T> {
private:
  bool started_;
  int gap_;
  T temp_;
  bool temp_set_;
  int i_;
  int j_;

public:
  ShellSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    started_ = false;
    gap_ = 0;
    temp_set_ = false;
    i_ = 0;
    j_ = 0;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "ShellSorter.tpp"