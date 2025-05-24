
#include "lib.hpp"

#include <string> // Ensure string is included for std::string operations

std::string Lib::helloWorldMsg() { return "Hello World!\n"; }

std::string Lib::processData(const std::string& data) {
    return "Processed: " + data;
}