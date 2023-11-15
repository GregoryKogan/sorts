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
  } catch (...) {
    log_red("FAILED");
    std::cout << ": " << name << std::endl;
    log_red("Unknown exception");
    std::cout << std::endl;
    return false;
  }
  log_green("PASSED");
  std::cout << ": " << name << std::endl;
  return true;
}

} // namespace kogan
