//
// Created by Gregory Kogan on 07.05.2023.
//

#include "colored_logs.hpp"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define END "\x1b[0m"

void log_red(const std::string &str) { printf(RED "%s" END, str.c_str()); }

void log_green(const std::string &str) { printf(GREEN "%s" END, str.c_str()); }

void log_blue(const std::string &str) { printf(BLUE "%s" END, str.c_str()); }
