#pragma once

#include <string>

class Lib {
   public:
    [[nodiscard]] static std::string helloWorldMsg();
    [[nodiscard]] static std::string processData(const std::string& data);
};