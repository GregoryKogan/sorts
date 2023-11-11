#include "HeapSorter.hpp"

namespace kogan {

template <class T> inline void HeapSorter<T>::sort_() {
  if (!started_) {
    i_ = this->sequence_->get_length() / 2 - 1;
    j_ = this->sequence_->get_length() - 1;

    heapifier_ =
        make_unique<Heapifier<T>>(this, i_, this->sequence_->get_length());

    started_ = true;
  }

  if (!initial_heapify_done_) {
    while (i_ >= 0) {
      heapifier_->heapify();
      if (!heapifier_->is_done())
        return;
      i_--;
      heapifier_ =
          make_unique<Heapifier<T>>(this, i_, this->sequence_->get_length());
    }
    initial_heapify_done_ = true;
  }

  if (!extracting_started_) {
    heapifier_ = make_unique<Heapifier<T>>(this, 0, j_);

    extracting_started_ = true;
  }

  while (j_ > 0) {
    if (!extracting_swap_done_) {
      this->swap_(0, j_);
      extracting_swap_done_ = true;
    }

    heapifier_->heapify();
    if (!heapifier_->is_done())
      return;

    j_--;
    extracting_swap_done_ = false;
    heapifier_ = make_unique<Heapifier<T>>(this, 0, j_);
  }
}

template <class T> inline void Heapifier<T>::heapify() {
  if (!started_) {
    largest_ = index_;
    l_ = 2 * index_ + 1;
    r_ = 2 * index_ + 2;

    started_ = true;
  }

  if (!left_checked_) {
    if (l_ < heap_size_) {
      if (!this->sorter_->step_())
        return;
      if (sorter_->cmp_wrapper_(sorter_->sequence_->get(l_),
                                sorter_->sequence_->get(largest_)) > 0)
        largest_ = l_;
    }

    left_checked_ = true;
  }

  if (!right_checked_) {
    if (r_ < heap_size_) {
      if (!this->sorter_->step_())
        return;
      if (sorter_->cmp_wrapper_(sorter_->sequence_->get(r_),
                                sorter_->sequence_->get(largest_)) > 0)
        largest_ = r_;
    }

    right_checked_ = true;
  }

  if (largest_ != index_) {
    if (!largest_swap_done_) {
      sorter_->swap_(index_, largest_);
      largest_swap_done_ = true;
    }

    if (!child_heapifier_initialized_) {
      child_heapifier_ =
          make_unique<Heapifier<T>>(sorter_, largest_, heap_size_);
      child_heapifier_initialized_ = true;
    }

    child_heapifier_->heapify();
    if (!child_heapifier_->is_done())
      return;
  }

  is_done_ = true;
}

template <class T>
inline SmartPtrLinkedListSequence<std::size_t>
Heapifier<T>::generate_interesting_indexes() const noexcept {
  SmartPtrLinkedListSequence<std::size_t> interesting_indexes;

  if (0 <= index_ && index_ < sorter_->sequence_->get_length())
    interesting_indexes.append(index_);

  if (child_heapifier_initialized_) {
    SmartPtrLinkedListSequence<std::size_t> child_interesting_indexes =
        child_heapifier_->generate_interesting_indexes();
    for (std::size_t i = 0; i < child_interesting_indexes.get_length(); i++)
      interesting_indexes.append(child_interesting_indexes[i]);
  }

  return interesting_indexes;
}

template <class T>
inline void HeapSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->clear();
  if (started_) {
    auto heapifier_interesting_indexes =
        heapifier_->generate_interesting_indexes();
    for (std::size_t i = 0; i < heapifier_interesting_indexes.get_length(); i++)
      this->interesting_indexes_->append(heapifier_interesting_indexes[i]);
  }
  if (!extracting_started_) {
    if (0 <= i_ && i_ < this->sequence_->get_length())
      this->interesting_indexes_->append(i_);
  } else {
    if (0 <= j_ && j_ < this->sequence_->get_length())
      this->interesting_indexes_->append(j_);
  }
}

} // namespace kogan