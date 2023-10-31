//
// Created by Gregory Kogan on 06.05.2023.
//

#include "Test.hpp"

namespace kogan {

Test::Test(std::string name, void (*testFunction)()) : name(std::move(name)), testFunction(testFunction) {}

bool Test::run() const {
    try {
        testFunction();
    } catch (const std::exception &e) {
        log_red("FAILED");
        std::cout << ": " << name << std::endl;
        log_red(e.what());
        std::cout << std::endl;
        return false;
    }
    log_green("PASSED");
    std::cout << ": " << name << std::endl;
    return true;
}

}  // namespace kogan
