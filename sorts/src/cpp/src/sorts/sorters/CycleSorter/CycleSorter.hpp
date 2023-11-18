#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class CycleSorter : public Sorter<T> {
private:
  int cycle_start_ = 0;
  bool position_found_ = false;
  int position_ = 0;
  int position_search_index_ = 0;
  bool rotation_complete_ = false;

public:
  CycleSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    cycle_start_ = 0;
    position_ = cycle_start_;
    position_search_index_ = cycle_start_ + 1;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "CycleSorter.tpp"