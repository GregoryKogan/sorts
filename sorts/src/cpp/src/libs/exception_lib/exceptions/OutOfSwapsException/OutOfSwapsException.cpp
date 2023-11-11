#include "OutOfSwapsException.hpp"

#include <utility>

namespace kogan {

void OutOfSwapsException::build_message() const {
  snprintf(message, MESSAGE_MAX_LENGTH,
           "(OutOfSwaps): no more swaps available");
}

} // namespace kogan