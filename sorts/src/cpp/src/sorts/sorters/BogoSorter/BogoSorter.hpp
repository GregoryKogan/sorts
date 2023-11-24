#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class BogoSorter : public Sorter<T> {
  bool checked_;
  bool sorted_;
  int i_;

  bool check_if_sorted_();
  bool shuffle_();

public:
  BogoSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    checked_ = false;
    sorted_ = false;
    i_ = 0;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "BogoSorter.tpp"