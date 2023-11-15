#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class CombSorter : public Sorter<T> {
private:
  int gap_ = 0;
  int i_ = 0;
  bool swapped_ = false;
  bool finished_ = false;

  void next_gap_();

public:
  CombSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    gap_ = this->sequence_->get_length();
    next_gap_();
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "CombSorter.tpp"