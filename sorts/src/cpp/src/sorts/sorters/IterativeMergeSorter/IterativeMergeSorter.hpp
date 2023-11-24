#pragma once

#include "../../smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class IterativeMergeSorter : public Sorter<T> {
private:
  std::size_t curr_size_;
  bool is_merging_;
  std::size_t left_;
  std::size_t middle_;
  std::size_t right_;
  std::size_t i_;
  std::size_t j_;
  std::size_t k_;
  bool buffers_filled_;
  SmartPtrArraySequence<int> left_part_;
  SmartPtrArraySequence<int> right_part_;

  bool merge_();

public:
  IterativeMergeSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    curr_size_ = 1;
    is_merging_ = false;
    left_ = 0;
    middle_ = 0;
    right_ = 0;
    i_ = 0;
    j_ = 0;
    k_ = 0;
    buffers_filled_ = false;
  }

  void sort_() override;

  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "IterativeMergeSorter.tpp"