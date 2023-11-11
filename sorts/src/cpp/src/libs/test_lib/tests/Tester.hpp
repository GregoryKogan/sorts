#pragma once

#include <vector>

#include "TestSuite.hpp"

namespace kogan {

class Tester {
  std::vector<kogan::TestSuite> test_suites;
  int total;
  int passed;

public:
  explicit Tester(std::vector<kogan::TestSuite> &suites);
  void test();
};

} // namespace kogan