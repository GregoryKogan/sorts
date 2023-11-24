#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class GnomeSorter : public Sorter<T> {
  int index_;

public:
  GnomeSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) { index_ = 0; }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "GnomeSorter.tpp"