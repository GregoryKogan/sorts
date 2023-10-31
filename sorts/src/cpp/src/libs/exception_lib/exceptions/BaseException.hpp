//
// Created by Gregory Kogan on 04.05.2023.
//

#ifndef LAB2_BASEEXCEPTION_H
#define LAB2_BASEEXCEPTION_H

#include <exception>
#include <string>

namespace kogan {

class BaseException : public std::exception {

protected:
  char *message;
  const size_t MESSAGE_MAX_LENGTH = 1024;

  virtual void build_message() const = 0;

public:
  BaseException();
  ~BaseException() override;

  [[nodiscard]] const char *what() const noexcept override;
};

} // namespace kogan

#endif // LAB2_BASEEXCEPTION_H
