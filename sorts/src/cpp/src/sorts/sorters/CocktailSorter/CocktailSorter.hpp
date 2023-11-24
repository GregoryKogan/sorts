#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class CocktailSorter : public Sorter<T> {
private:
  bool started_;
  bool forward_pass_done_;
  bool backward_pass_done_;
  bool swapped_;
  int start_;
  int end_;
  int i_;
  int j_;

public:
  CocktailSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    started_ = false;
    forward_pass_done_ = false;
    backward_pass_done_ = false;
    swapped_ = false;
    start_ = 0;
    end_ = 0;
    i_ = 0;
    j_ = 0;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "CocktailSorter.tpp"