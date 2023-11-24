#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class CycleSorter : public Sorter<T> {
  int cycle_start_;
  bool position_found_;
  int position_;
  int position_search_index_;
  bool rotation_complete_;

public:
  CycleSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    cycle_start_ = 0;
    position_found_ = false;
    position_ = cycle_start_;
    position_search_index_ = cycle_start_ + 1;
    rotation_complete_ = false;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "CycleSorter.tpp"