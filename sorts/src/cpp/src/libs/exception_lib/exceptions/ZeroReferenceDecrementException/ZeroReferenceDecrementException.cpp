#include "ZeroReferenceDecrementException.hpp"

void kogan::ZeroReferenceDecrementException::build_message() const {
    snprintf(message, MESSAGE_MAX_LENGTH,
             "(ZeroReferenceDecrement): can't decrement reference counter if it's already zero");
}