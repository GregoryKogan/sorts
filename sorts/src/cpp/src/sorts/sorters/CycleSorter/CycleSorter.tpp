#include "CycleSorter.hpp"

namespace kogan {

template <class T> inline void CycleSorter<T>::sort_() {
  while (cycle_start_ <= this->sequence_->get_length() - 2) {
    if (!position_found_) {
      while (position_search_index_ < this->sequence_->get_length()) {
        if (!this->step_()) return;

        if (this->cmp_wrapper_(this->sequence_->get(position_search_index_), this->sequence_->get(cycle_start_)) < 0)
          position_++;
        position_search_index_++;
      }
      position_found_ = true;

      if (position_ == cycle_start_) {
        cycle_start_++;
        position_ = cycle_start_;
        position_search_index_ = cycle_start_ + 1;
        position_found_ = false;
        continue;
      }

      while (this->cmp_wrapper_(this->sequence_->get(position_), this->sequence_->get(cycle_start_)) == 0) position_++;

      if (position_ != cycle_start_) this->swap_(position_, cycle_start_);

      if (position_ == cycle_start_) rotation_complete_ = true;
      else {
        position_ = cycle_start_;
        position_search_index_ = cycle_start_ + 1;
      }
    }

    if (!rotation_complete_) {
      while (true) {
        while (position_search_index_ < this->sequence_->get_length()) {
          if (!this->step_()) return;

          if (this->cmp_wrapper_(this->sequence_->get(position_search_index_), this->sequence_->get(cycle_start_)) < 0)
            position_++;

          position_search_index_++;
        }

        if (position_ == cycle_start_) break;

        while (this->cmp_wrapper_(this->sequence_->get(position_), this->sequence_->get(cycle_start_)) == 0)
          position_++;

        if (this->cmp_wrapper_(this->sequence_->get(position_), this->sequence_->get(cycle_start_)) != 0)
          this->swap_(position_, cycle_start_);

        if (position_ == cycle_start_) break;

        position_ = cycle_start_;
        position_search_index_ = cycle_start_ + 1;
      }
      rotation_complete_ = true;
    }

    cycle_start_++;
    position_ = cycle_start_;
    position_search_index_ = cycle_start_ + 1;
    position_found_ = false;
    rotation_complete_ = false;
  }
}

template <class T> inline void CycleSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->append(cycle_start_);
  this->interesting_indexes_->append(position_);
  this->interesting_indexes_->append(position_search_index_);
}

} // namespace kogan