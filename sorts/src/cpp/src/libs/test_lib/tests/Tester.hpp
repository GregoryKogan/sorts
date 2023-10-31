//
// Created by Gregory Kogan on 12.05.2023.
//

#ifndef SEQUENCE_LIB_TESTER_HPP
#define SEQUENCE_LIB_TESTER_HPP

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

}  // namespace kogan

#endif  // SEQUENCE_LIB_TESTER_HPP
