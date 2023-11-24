#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

class RadixSorter : public Sorter<int> {
  bool max_val_found_;
  int max_val_;
  int max_val_search_index_;

  bool count_sorting_;
  int exp_;
  bool output_array_filled_;
  int counting_array_index_;
  int output_array_index_;
  int i_;
  SmartPtrArraySequence<int> output_array_;
  SmartPtrArraySequence<int> counting_array_;

  bool find_max_value_();
  bool count_sort_();

public:
  RadixSorter(SharedPtr<SmartPtrSequence<int>> sequence) : Sorter<int>([](int a, int b) { return a - b; }, sequence) {
    max_val_found_ = false;
    max_val_ = sequence->get(0);
    max_val_search_index_ = 1;
    count_sorting_ = false;
    exp_ = 1;
    output_array_filled_ = false;
    counting_array_index_ = 0;
    output_array_index_ = -2;
    i_ = 0;
    output_array_.clear();
    output_array_.append(0);
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "RadixSorter.tpp"