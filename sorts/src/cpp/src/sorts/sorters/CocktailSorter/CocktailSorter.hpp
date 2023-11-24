#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class CocktailSorter : public Sorter<T> {
  bool forward_pass_done_;
  bool backward_pass_done_;
  bool swapped_;
  int start_;
  int end_;
  int i_;
  int j_;

public:
  CocktailSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    forward_pass_done_ = false;
    backward_pass_done_ = false;
    swapped_ = false;
    start_ = 0;
    end_ = sequence->get_length() - 1;
    i_ = start_;
    j_ = end_ - 1;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "CocktailSorter.tpp"