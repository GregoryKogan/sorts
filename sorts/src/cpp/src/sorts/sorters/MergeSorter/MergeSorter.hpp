#pragma once

#include "../../smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class MergeSorter : public Sorter<T> {
  int left_;
  int right_;
  int middle_;
  UniquePtr<MergeSorter<T>> left_sorter_;
  UniquePtr<MergeSorter<T>> right_sorter_;
  bool merged_;
  int i_;
  int j_;
  int k_;
  SmartPtrArraySequence<int> left_part_;
  SmartPtrArraySequence<int> right_part_;
  bool buffers_filled_ = false;
  bool is_merging_ = false;

  void set_range_(std::size_t left, std::size_t right) noexcept;
  bool merge_();

  SmartPtrLinkedListSequence<std::size_t> generate_interesting_indexes_() const noexcept;

public:
  MergeSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence) : Sorter<T>(cmp, sequence) {
    left_ = -1;
    right_ = -1;
    middle_ = 0;
    merged_ = false;
    i_ = 0;
    j_ = 0;
    k_ = 0;
    buffers_filled_ = false;
    is_merging_ = false;
  }

  void sort_() override;
  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "MergeSorter.tpp"