#include "exception_lib.hpp"

void exception_lib_is_working() {
    std::cout << "Test lib is working!" << std::endl;

    try {
        throw kogan::AssertionFailedException("test", __FILE__, __FUNCTION__, __LINE__);
    } catch (const std::exception &e) {
        log_red("ERROR: ");
        log_red(e.what());
        std::cout << std::endl;
    }

    try {
        throw kogan::EmptyContainerException();
    } catch (const std::exception &e) {
        log_red("ERROR: ");
        log_red(e.what());
        std::cout << std::endl;
    }

    try {
        throw kogan::IndexOutOfRangeException(42, 1, 10);
    } catch (const std::exception &e) {
        log_red("ERROR: ");
        log_red(e.what());
        std::cout << std::endl;
    }

    try {
        throw kogan::InvalidArgumentException("test");
    } catch (const std::exception &e) {
        log_red("ERROR: ");
        log_red(e.what());
        std::cout << std::endl;
    }
}