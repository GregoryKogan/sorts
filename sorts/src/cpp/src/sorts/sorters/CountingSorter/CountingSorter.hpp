#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

class CountingSorter : public Sorter<int> {
private:
  int max_value_;
  SmartPtrArraySequence<int> counting_array_;
  SmartPtrArraySequence<int> output_array_;

  bool max_value_found_;
  bool counting_array_filled_;
  bool output_written_;
  int i_;

public:
  CountingSorter(SharedPtr<SmartPtrSequence<int>> sequence)
      : Sorter<int>([](int a, int b) { return a - b; }, sequence) {
    max_value_ = 0;
    max_value_found_ = false;
    counting_array_filled_ = false;
    output_written_ = false;
    i_ = 0;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "CountingSorter.tpp"