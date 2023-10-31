//
// Created by Gregory Kogan on 04.05.2023.
//

#ifndef LAB2_INVALIDARGUMENTEXCEPTION_H
#define LAB2_INVALIDARGUMENTEXCEPTION_H

#include "../BaseException.hpp"

namespace kogan {

class InvalidArgumentException : public BaseException {
  std::string argument_name;

  void build_message() const override;

public:
  explicit InvalidArgumentException(std::string argument_name);
};

} // namespace kogan

#endif // LAB2_INVALIDARGUMENTEXCEPTION_H
