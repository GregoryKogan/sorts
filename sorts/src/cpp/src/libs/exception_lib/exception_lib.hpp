#ifndef EXCEPTION_LIB_HPP
#define EXCEPTION_LIB_HPP

#include <iostream>

#include "IO/colored_logs.hpp"
#include "exceptions/AssertionFailedException/AssertionFailedException.hpp"
#include "exceptions/EmptyContainerException/EmptyContainerException.hpp"
#include "exceptions/IndexOutOfRangeException/IndexOutOfRangeException.hpp"
#include "exceptions/InvalidArgumentException/InvalidArgumentException.hpp"

void exception_lib_is_working();

#endif