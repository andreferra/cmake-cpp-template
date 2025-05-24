#include <iostream>
#include "lib.hpp" // Assuming lib.hpp is in the include path

int main() {
    // Call the new static method
    std::string data = "Sample Data";
    std::string processedData = Lib::processData(data);
    std::cout << "Calling Lib::processData(\"" << data << "\"): " << processedData << std::endl;

    // Call the existing static method for completeness
    std::cout << "Calling Lib::helloWorldMsg(): " << Lib::helloWorldMsg(); // helloWorldMsg already includes a newline

    return 0;
}
