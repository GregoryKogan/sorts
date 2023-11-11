#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

class RadixSorter : public Sorter<int> {
private:
  bool started_ = false;
  bool max_val_found_ = false;
  int max_val_;
  int max_val_search_index_ = 0;

  bool count_sorting_ = false;
  int exp_ = 1;
  SmartPtrArraySequence<int> output_array_;
  SmartPtrArraySequence<int> counting_array_;

  bool find_max_value_();
  bool count_sort_();

public:
  RadixSorter(int (*cmp)(int, int), SharedPtr<SmartPtrSequence<int>> sequence)
      : Sorter<int>(cmp, sequence) {}

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "RadixSorter.tpp"