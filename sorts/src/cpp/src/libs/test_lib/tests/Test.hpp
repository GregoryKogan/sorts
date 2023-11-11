#pragma once

#include <iostream>
#include <string>

#include "../../exception_lib/IO/colored_logs.hpp"

namespace kogan {

class Test {
  std::string name;
  void (*testFunction)();

public:
  Test(std::string name, void (*testFunction)());
  [[nodiscard]] bool run() const;
};

} // namespace kogan