//
// Created by Gregory Kogan on 04.05.2023.
//

#include "EmptyContainerException.hpp"

namespace kogan {

void EmptyContainerException::build_message() const {
  snprintf(message, MESSAGE_MAX_LENGTH,
           "(EmptyContainer): can't get item from empty container");
}

} // namespace kogan
