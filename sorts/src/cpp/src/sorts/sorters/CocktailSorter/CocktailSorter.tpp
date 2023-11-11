#include "CocktailSorter.hpp"

namespace kogan {

template <class T> inline void CocktailSorter<T>::sort_() {
  std::size_t n = this->sequence_->get_length();

  if (!started_) {
    start_ = 0;
    end_ = n - 1;
    i_ = start_;
    j_ = end_ - 1;
    swapped_ = false;

    started_ = true;
  }

  while (true) {
    if (!forward_pass_done_) {
      while (i_ < end_) {
        if (!this->step_())
          return;

        if (this->cmp_wrapper_(this->sequence_->get(i_),
                               this->sequence_->get(i_ + 1)) > 0) {
          this->swap_(i_, i_ + 1);
          swapped_ = true;
        }
        i_++;
      }

      if (!swapped_)
        break;
      end_--;
      swapped_ = false;

      forward_pass_done_ = true;
    }

    if (!backward_pass_done_) {
      while (j_ >= start_) {
        if (!this->step_())
          return;

        if (this->cmp_wrapper_(this->sequence_->get(j_),
                               this->sequence_->get(j_ + 1)) > 0) {
          this->swap_(j_, j_ + 1);
          swapped_ = true;
        }
        j_--;
      }
      if (!swapped_)
        break;
      start_++;
      swapped_ = false;

      backward_pass_done_ = true;
    }

    i_ = start_;
    j_ = end_ - 1;

    forward_pass_done_ = false;
    backward_pass_done_ = false;
  }
}

template <class T>
inline void CocktailSorter<T>::set_interesting_indexes_() noexcept {
  this->interesting_indexes_->clear();
  this->interesting_indexes_->append(start_);
  this->interesting_indexes_->append(end_);
  if (!forward_pass_done_)
    this->interesting_indexes_->append(i_);
  else
    this->interesting_indexes_->append(j_);
}

} // namespace kogan