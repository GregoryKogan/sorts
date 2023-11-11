#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class CocktailSorter : public Sorter<T> {
private:
  bool started_ = false;
  bool forward_pass_done_ = false;
  bool backward_pass_done_ = false;
  bool swapped_ = false;
  int start_ = 0;
  int end_ = 0;
  int i_ = 0;
  int j_ = 0;

public:
  CocktailSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence)
      : Sorter<T>(cmp, sequence) {}

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "CocktailSorter.tpp"