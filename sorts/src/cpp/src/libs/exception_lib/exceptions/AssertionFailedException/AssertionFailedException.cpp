//
// Created by Gregory Kogan on 07.05.2023.
//

#include "AssertionFailedException.hpp"

namespace kogan {

void AssertionFailedException::build_message() const {
    snprintf(message, MESSAGE_MAX_LENGTH, "(AssertionFailed): (%s), file %s, function %s, line %d", expression.c_str(),
             file.c_str(), function_name.c_str(), line);
}

AssertionFailedException::AssertionFailedException(const std::string &expression, const char *file,
                                                   const char *function_name, int line) {
    this->expression = expression;
    std::string full_filename = file;
    std::string token = full_filename.substr(full_filename.rfind('/') + 1, full_filename.length());
    this->file = token;
    this->function_name = function_name;
    this->line = line;
}

}  // namespace kogan
