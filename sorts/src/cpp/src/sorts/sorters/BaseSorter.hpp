#pragma once

#include <optional>

#include "../smart_sequences/sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp"

namespace kogan {

template <class T> class Sorter {
protected:
  int (*cmp_)(T, T);
  SharedPtr<SmartPtrSequence<T>> sequence_;

  SharedPtr<SmartPtrLinkedListSequence<T>> interesting_indexes_;

  u_int32_t comparisons_ = 0;
  u_int32_t swaps_ = 0;

  bool limited_ = false;
  u_int32_t available_steps_ = 0;

  bool is_sorted_ = false;

public:
  Sorter(int (*cmp)(T, T), SharedPtr<SmartPtrSequence<T>> sequence);

  virtual ~Sorter() = default;

  // Observers
  [[nodiscard]] bool is_sorted() const noexcept;
  [[nodiscard]] SharedPtr<SmartPtrLinkedListSequence<T>> get_interesting_indexes() const noexcept;
  [[nodiscard]] u_int32_t get_comparisons() const noexcept;
  [[nodiscard]] u_int32_t get_swaps() const noexcept;
  [[nodiscard]] u_int32_t get_available_steps() const noexcept;
  [[nodiscard]] bool is_limited() const noexcept;

  // Modifiers
  void add_available_steps(u_int32_t available_steps) noexcept;
  void make_limited() noexcept;
  void make_unlimited() noexcept;

  void sort();

protected:
  virtual void sort_() = 0;
  virtual void set_interesting_indexes_() noexcept = 0;

  bool step_() noexcept;

  int cmp_wrapper_(T a, T b);
  void swap_(int i, int j);
};

} // namespace kogan

#include "BaseSorter.tpp"