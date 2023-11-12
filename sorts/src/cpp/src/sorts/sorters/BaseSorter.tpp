#include "BaseSorter.hpp"

namespace kogan {

template <class T>
inline Sorter<T>::Sorter(int (*cmp)(T, T),
                         SharedPtr<SmartPtrSequence<T>> sequence)
    : cmp_(cmp), sequence_(sequence) {
  comparisons_ = 0;
  swaps_ = 0;
  interesting_indexes_ = make_shared<SmartPtrLinkedListSequence<T>>();
}

template <class T> inline bool Sorter<T>::is_sorted() const noexcept {
  if (sequence_->get_length() < 2)
    return true;
  for (std::size_t i = 0; i < sequence_->get_length() - 1; ++i) {
    if (cmp_(sequence_->get(i), sequence_->get(i + 1)) > 0)
      return false;
  }
  return true;
}

template <class T>
inline SharedPtr<SmartPtrLinkedListSequence<T>>
Sorter<T>::get_interesting_indexes() const noexcept {
  return interesting_indexes_;
}

template <class T>
inline u_int32_t Sorter<T>::get_comparisons() const noexcept {
  return comparisons_;
}

template <class T> inline u_int32_t Sorter<T>::get_swaps() const noexcept {
  return swaps_;
}

template <class T>
u_int32_t kogan::Sorter<T>::get_available_steps() const noexcept {
  return available_steps_;
}

template <class T> inline bool kogan::Sorter<T>::is_limited() const noexcept {
  return limited_;
}

template <class T>
inline void
kogan::Sorter<T>::add_available_steps(u_int32_t available_steps) noexcept {
  available_steps_ += available_steps;
}

template <class T> inline void kogan::Sorter<T>::make_limited() noexcept {
  limited_ = true;
  available_steps_ = 0;
}

template <class T> inline void kogan::Sorter<T>::make_unlimited() noexcept {
  limited_ = false;
  available_steps_ = 0;
}

template <class T> inline void Sorter<T>::sort() {
  if (sequence_->get_length() < 2)
    return;
  sort_();
  set_interesting_indexes_();
}

template <class T> inline bool kogan::Sorter<T>::step_() noexcept {
  if (!limited_)
    return true;

  if (!available_steps_)
    return false;

  --available_steps_;
  return true;
}

template <class T> inline int Sorter<T>::cmp_wrapper_(T a, T b) {
  ++comparisons_;
  return cmp_(a, b);
}

template <class T> inline void Sorter<T>::swap_(int i, int j) {
  ++swaps_;
  T tmp = sequence_->get(i);
  sequence_->set(i, sequence_->get(j));
  sequence_->set(j, tmp);
}

} // namespace kogan