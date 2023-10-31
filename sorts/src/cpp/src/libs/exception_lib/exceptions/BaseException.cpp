//
// Created by Gregory Kogan on 04.05.2023.
//

#include "BaseException.hpp"

namespace kogan {

BaseException::BaseException() { message = new char[MESSAGE_MAX_LENGTH]; }

BaseException::~BaseException() { delete[] message; }

const char *BaseException::what() const noexcept {
  build_message();
  return message;
}

} // namespace kogan
