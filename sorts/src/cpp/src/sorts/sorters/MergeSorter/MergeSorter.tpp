#include "MergeSorter.hpp"

namespace kogan {

template <class T>
inline void MergeSorter<T>::set_range_(std::size_t left,
                                       std::size_t right) noexcept {
  left_ = left;
  right_ = right;
  middle_ = left_ + (right_ - left_) / 2;

  if (left_ >= right_) {
    merged_ = true;
    return;
  }

  left_sorter_ = make_unique<MergeSorter<T>>(this->cmp_, this->sequence_);
  right_sorter_ = make_unique<MergeSorter<T>>(this->cmp_, this->sequence_);

  if (this->is_limited()) {
    left_sorter_->make_limited();
    right_sorter_->make_limited();
  }

  left_sorter_->set_range_(left_, middle_);
  right_sorter_->set_range_(middle_ + 1, right_);
}

template <class T> inline void MergeSorter<T>::sort_() {
  if (merged_) return;

  if (left_ == -1 && right_ == -1)
    set_range_(0, this->sequence_->get_length() - 1);

  if (!left_sorter_->merged_) {
    left_sorter_->add_available_steps(this->get_available_steps());
    left_sorter_->sort_();
    this->available_steps_ = left_sorter_->get_available_steps();
  }
  if (!right_sorter_->merged_) {
    right_sorter_->add_available_steps(this->get_available_steps());
    right_sorter_->sort_();
    this->available_steps_ = right_sorter_->get_available_steps();
  }

  if (this->is_limited() && !this->get_available_steps()) return;

  if (merge_()) {
    merged_ = true;
    is_merging_ = false;
    this->comparisons_ +=
        left_sorter_->get_comparisons() + right_sorter_->get_comparisons();
  }
}

template <class T> inline bool MergeSorter<T>::merge_() {
  std::size_t left_length = middle_ - left_ + 1;
  std::size_t right_length = right_ - middle_;

  if (!is_merging_) {
    left_part_.clear();
    right_part_.clear();
    for (std::size_t i = 0; i < left_length; ++i)
      left_part_.append(this->sequence_->get(left_ + i));
    for (std::size_t i = 0; i < right_length; ++i)
      right_part_.append(this->sequence_->get(middle_ + 1 + i));

    i_ = 0;
    j_ = 0;
    k_ = left_;
  }
  is_merging_ = true;

  while (i_ < left_length && j_ < right_length) {
    if (!this->step_()) return false;

    if (this->cmp_wrapper_(left_part_[i_], right_part_[j_]) <= 0) {
      this->sequence_->set(k_, left_part_[i_]);
      ++i_;
    } else {
      this->sequence_->set(k_, right_part_[j_]);
      ++j_;
    }
    ++k_;
  }

  while (i_ < left_length) {
    this->sequence_->set(k_, left_part_[i_]);
    ++i_;
    ++k_;
  }
  while (j_ < right_length) {
    this->sequence_->set(k_, right_part_[j_]);
    ++j_;
    ++k_;
  }

  return true;
}

template <class T>
inline SmartPtrLinkedListSequence<std::size_t>
MergeSorter<T>::generate_interesting_indexes_() const noexcept {
  SmartPtrLinkedListSequence<std::size_t> interesting_indexes;
  if (left_sorter_ && right_sorter_) {
    auto left_indexes = left_sorter_->generate_interesting_indexes_();
    auto right_indexes = right_sorter_->generate_interesting_indexes_();
    for (std::size_t i = 0; i < left_indexes.get_length(); ++i)
      interesting_indexes.append(left_indexes[i]);
    for (std::size_t i = 0; i < right_indexes.get_length(); ++i)
      interesting_indexes.append(right_indexes[i]);
  }
  if (!is_merging_) return interesting_indexes;

  interesting_indexes.append(left_);
  interesting_indexes.append(right_);
  interesting_indexes.append(middle_);
  interesting_indexes.append(left_ + i_);
  interesting_indexes.append(middle_ + 1 + j_);
  return interesting_indexes;
}

template <class T>
inline void MergeSorter<T>::set_interesting_indexes_() noexcept {
  auto my_interesting_indexes = generate_interesting_indexes_();
  for (std::size_t i = 0; i < my_interesting_indexes.get_length(); ++i)
    this->interesting_indexes_->append(my_interesting_indexes[i]);
}

} // namespace kogan