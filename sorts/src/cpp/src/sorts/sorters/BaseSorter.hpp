#pragma once

#include <optional>

#include "../../libs/exception_lib/exceptions/OutOfComparisonsException/OutOfComparisonsException.hpp"
#include "../../libs/exception_lib/exceptions/OutOfSwapsException/OutOfSwapsException.hpp"
#include "../smart_sequences/sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp"

namespace kogan {

template <class T> class Sorter {
protected:
  int (*cmp_)(T, T);
  SharedPtr<SmartPtrSequence<T>> sequence_;

  SharedPtr<SmartPtrLinkedListSequence<T>> interesting_indexes_;

  u_int32_t comparisons_ = 0;
  u_int32_t swaps_ = 0;

  bool limited_in_comparisons_ = false;
  bool limited_in_swaps_ = false;
  u_int32_t available_comparisons_ = 0;
  u_int32_t available_swaps_ = 0;

public:
  Sorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence);

  virtual ~Sorter() = default;

  // Observers
  [[nodiscard]] bool is_sorted() const noexcept;
  [[nodiscard]] SharedPtr<SmartPtrLinkedListSequence<T>>
  get_interesting_indexes() const noexcept;
  [[nodiscard]] [[nodiscard]] u_int32_t get_comparisons() const noexcept;
  [[nodiscard]] u_int32_t get_swaps() const noexcept;
  [[nodiscard]] u_int32_t get_available_comparisons() const noexcept;
  [[nodiscard]] u_int32_t get_available_swaps() const noexcept;
  [[nodiscard]] bool is_limited_in_comparisons() const noexcept;
  [[nodiscard]] bool is_limited_in_swaps() const noexcept;

  // Modifiers
  void add_available_comparisons(u_int32_t available_comparisons) noexcept;
  void add_available_swaps(u_int32_t available_swaps) noexcept;
  void make_limited_in_comparisons() noexcept;
  void make_limited_in_swaps() noexcept;
  void make_unlimited_in_comparisons() noexcept;
  void make_unlimited_in_swaps() noexcept;

  void sort();

protected:
  virtual void sort_() = 0;
  virtual void set_interesting_indexes_() noexcept = 0;

  std::optional<int> cmp_wrapper_(T a, T b);
  bool swap_(int i, int j);
};

} // namespace kogan

#include "BaseSorter.tpp"