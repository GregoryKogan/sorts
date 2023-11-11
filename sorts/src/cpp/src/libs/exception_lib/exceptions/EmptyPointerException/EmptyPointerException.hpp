#pragma once

#include "../BaseException.hpp"

namespace kogan {

class EmptyPointerException : public BaseException {
  void build_message() const override;
};

} // namespace kogan