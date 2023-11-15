#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

class CountingSorter : public Sorter<int> {
private:
  int max_value_ = 0;
  SmartPtrArraySequence<int> counting_array_;
  SmartPtrArraySequence<int> output_array_;

  bool max_value_found_ = false;
  bool counting_array_filled_ = false;
  bool output_written_ = false;
  int i_ = 0;

public:
  CountingSorter(SharedPtr<SmartPtrSequence<int>> sequence)
      : Sorter<int>([](int a, int b) { return a - b; }, sequence) {}

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "CountingSorter.tpp"