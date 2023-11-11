#pragma once

#include "../BaseException.hpp"

namespace kogan {

class EmptyContainerException : public BaseException {
  void build_message() const override;
};

} // namespace kogan
