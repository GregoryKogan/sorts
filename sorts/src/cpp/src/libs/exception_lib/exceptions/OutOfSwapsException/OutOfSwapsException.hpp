#pragma once

#include "../BaseException.hpp"

namespace kogan {

class OutOfSwapsException : public BaseException {
  void build_message() const override;

public:
  explicit OutOfSwapsException() = default;
};

} // namespace kogan