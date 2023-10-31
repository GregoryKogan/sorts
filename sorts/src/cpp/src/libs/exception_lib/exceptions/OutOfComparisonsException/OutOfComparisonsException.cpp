#include "OutOfComparisonsException.hpp"

#include <utility>

namespace kogan {

void OutOfComparisonsException::build_message() const {
    snprintf(message, MESSAGE_MAX_LENGTH, "(OutOfComparisons): no more comparisons available");
}

}  // namespace kogan