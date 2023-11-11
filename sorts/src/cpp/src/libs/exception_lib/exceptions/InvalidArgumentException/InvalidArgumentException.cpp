#include "InvalidArgumentException.hpp"

#include <utility>

namespace kogan {

InvalidArgumentException::InvalidArgumentException(std::string argument_name) {
  this->argument_name = std::move(argument_name);
}

void InvalidArgumentException::build_message() const {
  snprintf(message, MESSAGE_MAX_LENGTH,
           "(InvalidArgument): value of the %s argument is invalid",
           argument_name.c_str());
}

} // namespace kogan
