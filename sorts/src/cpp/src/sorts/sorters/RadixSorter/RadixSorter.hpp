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
  bool output_array_filled_ = false;
  int counting_array_index_ = 0;
  int output_array_index_ = -2;
  int i_ = 0;
  SmartPtrArraySequence<int> output_array_;
  SmartPtrArraySequence<int> counting_array_;

  bool find_max_value_();
  bool count_sort_();

public:
  RadixSorter(SharedPtr<SmartPtrSequence<int>> sequence) : Sorter<int>([](int a, int b) { return a - b; }, sequence) {}

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "RadixSorter.tpp"