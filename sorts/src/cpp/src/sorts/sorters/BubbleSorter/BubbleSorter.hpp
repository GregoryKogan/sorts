#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class BubbleSorter : public Sorter<T> {
private:
  int i_;
  int j_;

public:
  BubbleSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    i_ = 0;
    j_ = 0;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "BubbleSorter.tpp"