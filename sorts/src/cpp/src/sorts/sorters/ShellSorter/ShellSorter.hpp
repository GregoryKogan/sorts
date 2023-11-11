#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class ShellSorter : public Sorter<T> {
private:
  bool started_ = false;
  int gap_ = 0;
  T temp_;
  bool temp_set_ = false;
  int i_ = 0;
  int j_ = 0;

public:
  ShellSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence)
      : Sorter<T>(cmp, sequence) {}

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "ShellSorter.tpp"