#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class GnomeSorter : public Sorter<T> {
private:
  int index_ = 0;

public:
  GnomeSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence)
      : Sorter<T>(cmp, sequence) {}

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "GnomeSorter.tpp"