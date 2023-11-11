#pragma once

#include "../BaseSorter.hpp"

namespace kogan {

template <class T> class MergeSorter : public Sorter<T> {
private:
  std::size_t left_ = -1;
  std::size_t right_ = -1;
  std::size_t middle_ = 0;
  UniquePtr<MergeSorter<T>> left_sorter_;
  UniquePtr<MergeSorter<T>> right_sorter_;
  bool merged_ = false;
  std::size_t i_ = 0;
  std::size_t j_ = 0;
  std::size_t k_ = 0;
  SmartPtrLinkedListSequence<int> left_part_;
  SmartPtrLinkedListSequence<int> right_part_;
  bool is_merging_ = false;

  void set_range_(std::size_t left, std::size_t right) noexcept;
  bool merge_();

  SmartPtrLinkedListSequence<std::size_t>
  generate_interesting_indexes_() const noexcept;

public:
  MergeSorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence)
      : Sorter<T>(cmp, sequence) {}

  void sort_() override;

  void set_interesting_indexes_() noexcept override;
};

} // namespace kogan

#include "MergeSorter.tpp"