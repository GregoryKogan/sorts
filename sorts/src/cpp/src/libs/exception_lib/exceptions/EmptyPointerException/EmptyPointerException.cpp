#include "EmptyPointerException.hpp"

void kogan::EmptyPointerException::build_message() const {
    snprintf(message, MESSAGE_MAX_LENGTH, "(EmptyPointer): can't use empty pointer");
}