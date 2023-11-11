#pragma once

#include "../BaseException.hpp"

namespace kogan {

class InvalidArgumentException : public BaseException {
  std::string argument_name;

  void build_message() const override;

public:
  explicit InvalidArgumentException(std::string argument_name);
};

} // namespace kogan