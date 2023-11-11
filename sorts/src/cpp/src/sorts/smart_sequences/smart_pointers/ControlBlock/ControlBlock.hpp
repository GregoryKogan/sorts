#pragma once

#include "../../../../libs/exception_lib/exceptions/InvalidArgumentException/InvalidArgumentException.hpp"
#include "../../../../libs/exception_lib/exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.hpp"

namespace kogan {

template <class T> class ControlBlock {
private:
  T *ptr_;
  unsigned int reference_counter_;
  unsigned int weak_ptr_reference_counter_;

public:
  explicit ControlBlock(T *ptr); // constructor from pointer

  void increment_reference_counter() noexcept;
  void decrement_reference_counter_and_delete_if_zero();
  void increment_weak_ptr_reference_counter() noexcept;
  void decrement_weak_ptr_reference_counter_and_delete_if_zero();

  T *get() const noexcept;
  [[nodiscard]] unsigned int get_reference_counter() const noexcept;
  [[nodiscard]] unsigned int get_weak_ptr_reference_counter() const noexcept;
};

template <class T> class ControlBlock<T[]> { // specialization for arrays
private:
  T *ptr_;
  unsigned int reference_counter_;
  unsigned int weak_ptr_reference_counter_;

public:
  explicit ControlBlock(T *ptr);

  void increment_reference_counter() noexcept;
  void decrement_reference_counter_and_delete_if_zero();
  void increment_weak_ptr_reference_counter() noexcept;
  void decrement_weak_ptr_reference_counter_and_delete_if_zero();

  T *get() const noexcept;
  [[nodiscard]] unsigned int get_reference_counter() const noexcept;
  [[nodiscard]] unsigned int get_weak_ptr_reference_counter() const noexcept;
};

} // namespace kogan

#include "ControlBlock.tpp"