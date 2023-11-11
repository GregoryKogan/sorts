#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

class CountingSorter : public Sorter<int> {
private:
  int max_value_ = 0;
  SmartPtrArraySequence<int> counting_array_;
  SmartPtrArraySequence<int> output_array_;

  bool max_value_found_ = false;
  int i_ = 0;

public:
  CountingSorter(int (*cmp)(int, int),
                 SharedPtr<SmartPtrSequence<int>> sequence)
      : Sorter<int>(cmp, sequence) {}

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "CountingSorter.tpp"