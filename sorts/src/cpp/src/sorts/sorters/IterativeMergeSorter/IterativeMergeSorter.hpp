#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class IterativeMergeSorter : public Sorter<T> {
private:
  std::size_t curr_size_ = 1;
  bool is_merging_ = false;
  std::size_t left_ = 0;
  std::size_t middle_ = 0;
  std::size_t right_ = 0;
  std::size_t i_ = 0;
  std::size_t j_ = 0;
  std::size_t k_ = 0;
  SmartPtrLinkedListSequence<int> left_part_;
  SmartPtrLinkedListSequence<int> right_part_;

  bool merge_();

public:
  IterativeMergeSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {}

  void sort_() override;

  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "IterativeMergeSorter.tpp"