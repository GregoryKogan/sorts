//
// Created by Gregory Kogan on 04.05.2023.
//

#include "IndexOutOfRangeException.hpp"

namespace kogan {

IndexOutOfRangeException::IndexOutOfRangeException(int index, int range_min,
                                                   int range_max) {
  this->index = index;
  this->range_min = range_min;
  this->range_max = range_max;
}

void IndexOutOfRangeException::build_message() const {
  if (range_max < range_min) {
    snprintf(message, MESSAGE_MAX_LENGTH,
             "(IndexOutOfRange): index %d is out of empty range", index);
  } else {
    snprintf(message, MESSAGE_MAX_LENGTH,
             "(IndexOutOfRange): index %d is out of range [%d, %d]", index,
             range_min, range_max);
  }
}

} // namespace kogan
