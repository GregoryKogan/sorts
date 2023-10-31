//
// Created by Gregory Kogan on 06.05.2023.
//

#include "TestSuite.hpp"

namespace kogan {

TestSuite::TestSuite(std::string name) { this->name = std::move(name); }

size_t TestSuite::add_test(const Test &test) {
    tests.push_back(test);
    return tests.size();
}

int TestSuite::get_tests_count() { return (int)tests.size(); }

int TestSuite::run() {
    log_blue(name);
    std::cout << " test suite is running" << std::endl;

    int tests_passed_counter = 0;
    for (const auto &test : tests) tests_passed_counter += test.run();

    if (tests_passed_counter == get_tests_count()) {
        log_green("All tests in ");
        log_blue(name);
        log_green(" suite passed!\n\n");
    } else {
        log_red("Some tests in ");
        log_blue(name);
        log_red(" suite failed\n\n");
    }

    return tests_passed_counter;
}

}  // namespace kogan
