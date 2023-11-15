#include "StoogeSorter.hpp"

namespace kogan {

template <class T> inline void StoogeSorter<T>::sort_() {
  if (finished_) return;

  if (l_ == -1 && r_ == -1) set_range_(0, this->sequence_->get_length() - 1);
  if (finished_) return;

  if (!ends_checked_) {
    if (!this->step_()) return;
    if (this->cmp_wrapper_(this->sequence_->get(l_), this->sequence_->get(r_)) > 0) { this->swap_(l_, r_); }
    ends_checked_ = true;
  }

  if (r_ - l_ + 1 > 2) {
    if (!first_sorter_->finished_) {
      first_sorter_->add_available_steps(this->get_available_steps());
      first_sorter_->sort_();
      this->available_steps_ = first_sorter_->get_available_steps();
      if (this->is_limited() && !this->available_steps_) return;
    }
    if (!second_sorter_->finished_) {
      second_sorter_->add_available_steps(this->get_available_steps());
      second_sorter_->sort_();
      this->available_steps_ = second_sorter_->get_available_steps();
      if (this->is_limited() && !this->available_steps_) return;
    }
    if (!third_sorter_->finished_) {
      third_sorter_->add_available_steps(this->get_available_steps());
      third_sorter_->sort_();
      this->available_steps_ = third_sorter_->get_available_steps();
      if (this->is_limited() && !this->available_steps_) return;
    }
  }

  this->comparisons_ +=
      first_sorter_->get_comparisons() + second_sorter_->get_comparisons() + third_sorter_->get_comparisons();
  this->swaps_ += first_sorter_->get_swaps() + second_sorter_->get_swaps() + third_sorter_->get_swaps();
  finished_ = true;
}

template <class T> inline void StoogeSorter<T>::set_range_(int l, int r) {
  l_ = l;
  r_ = r;

  if (l_ >= r_) {
    finished_ = true;
    return;
  }

  if (r_ - l_ + 1 > 2) {
    int t = (r_ - l_ + 1) / 3;
    first_sorter_ = make_unique<StoogeSorter<T>>(this->cmp_, this->sequence_);
    second_sorter_ = make_unique<StoogeSorter<T>>(this->cmp_, this->sequence_);
    third_sorter_ = make_unique<StoogeSorter<T>>(this->cmp_, this->sequence_);

    if (this->is_limited()) {
      first_sorter_->make_limited();
      second_sorter_->make_limited();
      third_sorter_->make_limited();
    }

    first_sorter_->set_range_(l_, r_ - t);
    second_sorter_->set_range_(l_ + t, r_);
    third_sorter_->set_range_(l_, r_ - t);
  }
}

template <class T>
inline SmartPtrArraySequence<std::size_t> StoogeSorter<T>::generate_interesting_indexes_() const noexcept {
  auto interesting_indexes = SmartPtrArraySequence<std::size_t>();
  if ((l_ == -1 && r_ == -1) || finished_) return interesting_indexes;
  interesting_indexes.append(l_);
  interesting_indexes.append(r_);
  if (r_ - l_ + 1 > 2) {
    if (!first_sorter_->finished_) {
      auto first_interesting_indexes = first_sorter_->generate_interesting_indexes_();
      for (std::size_t i = 0; i < first_interesting_indexes.get_length(); ++i)
        interesting_indexes.append(first_interesting_indexes[i]);
      return interesting_indexes;
    }
    if (!second_sorter_->finished_) {
      auto second_interesting_indexes = second_sorter_->generate_interesting_indexes_();
      for (std::size_t i = 0; i < second_interesting_indexes.get_length(); ++i)
        interesting_indexes.append(second_interesting_indexes[i]);
      return interesting_indexes;
    }
    if (!third_sorter_->finished_) {
      auto third_interesting_indexes = third_sorter_->generate_interesting_indexes_();
      for (std::size_t i = 0; i < third_interesting_indexes.get_length(); ++i)
        interesting_indexes.append(third_interesting_indexes[i]);
      return interesting_indexes;
    }
  }
  return interesting_indexes;
}

template <class T> inline void StoogeSorter<T>::set_interesting_indexes_() noexcept {
  auto interesting_indexes = generate_interesting_indexes_();
  for (std::size_t i = 0; i < interesting_indexes.get_length(); ++i)
    this->interesting_indexes_->append(interesting_indexes[i]);
}

} // namespace kogan