//
// Created by Gregory Kogan on 12.05.2023.
//

#include "Tester.hpp"

namespace kogan {

Tester::Tester(std::vector<kogan::TestSuite> &suites) {
    total = 0;
    passed = 0;
    for (const kogan::TestSuite &suite : suites) test_suites.push_back(suite);
}

void Tester::test() {
    for (kogan::TestSuite suite : test_suites) {
        total += suite.get_tests_count();
        passed += suite.run();
    }

    std::cout << "TOTAL: " << total << ", PASSED: " << passed << std::endl;
    if (passed == total)
        log_green("All tests passed!\n");
    else
        log_red("Some tests failed\n");
}

}  // namespace kogan
