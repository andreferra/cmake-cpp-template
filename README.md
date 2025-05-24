# C++ CMake Project Template

## Project Overview

This is a modern C++ project template using CMake for building robust and maintainable applications. It provides a structured starting point with integrated testing, support for compiler sanitizers, and best practices for C++ development.

**Key Features:**
- **Modern C++17** standard
- **Modular structure** with separate library (`src/`) and application (`app/`)
- **Integrated testing** with GoogleTest (`test/`)
- **Compiler Sanitizer Support** (ASan, TSan, UBSan) for runtime bug detection
- **Build optimization** with ccache support (if installed)
- **Cross-platform** compatibility
- **Out-of-source builds** enforced
- **Compile commands** generation (`compile_commands.json`) for IDE and tooling support (e.g., Clangd)

## Project Structure

```
├── app/                 # Main application source code
├── src/                 # Library source code
├── test/                # Unit tests (GoogleTest)
├── cmake/               # CMake utility scripts and modules
└── CMakeLists.txt       # Root CMake configuration file
```

## Requirements

- CMake 3.14 or higher
- C++17 compatible compiler (e.g., GCC, Clang, MSVC)
- Optional: Ninja build system for faster builds
- Optional: ccache for build caching

## Quick Start

### Basic Build (using default Makefiles)

```bash
cmake -S . -B build
cmake --build build
```

### Recommended Build (with Ninja)

For significantly faster build times, especially on larger projects, using Ninja as the CMake generator is highly recommended.

```bash
cmake -S . -B build -GNinja
cmake --build build
```

### Running the Application

After a successful build, the main application executable will be located at:
```bash
./build/app/project_template
```

## Build Configuration Options

You can customize the build process by passing options to CMake using the `-D<OPTION_NAME>=<VALUE>` syntax.

| Option             | Description                                       | Default |
|--------------------|---------------------------------------------------|---------|
| `ENABLE_TESTING`   | Enable building test applications                 | `OFF`   |
| `WARNINGS_AS_ERRORS` | Treat compiler warnings as errors                 | `OFF`   |
| `ENABLE_ASAN`      | Enable AddressSanitizer                           | `OFF`   |
| `ENABLE_TSAN`      | Enable ThreadSanitizer (often mutually exclusive with ASAN) | `OFF`   |
| `ENABLE_UBSAN`     | Enable UndefinedBehaviorSanitizer                 | `OFF`   |

### Example with Options

This command enables testing and treats warnings as errors:
```bash
cmake -S . -B build -GNinja -DENABLE_TESTING=ON -DWARNINGS_AS_ERRORS=ON
cmake --build build
```

## Using the Library

The `project_template_lib` (defined in `src/`) provides a `Lib` class. Here's an example of how you might use it in your `app/main.cpp`:

```cpp
// app/main.cpp

#include <iostream>
#include <string>
#include "lib.h" // Main header for your library (ProjectTemplate::Lib)

int main(int argc, char *argv[]) {
    ProjectTemplate::Lib lib;

    // Using the existing helloWorldMsg
    std::cout << lib.helloWorldMsg() << std::endl;

    // Example: Using a hypothetical function that processes data
    // (You would need to add `processData` to src/lib.h and src/lib.cpp)
    if (argc > 1) {
        std::string data_to_process = argv[1];
        // std::string processed_data = lib.processData(data_to_process); // Hypothetical
        // std::cout << "Processed data: " << processed_data << std::endl;
        std::cout << "Data to process (hypothetical): " << data_to_process << std::endl;
    } else {
        std::cout << "No data provided for processing." << std::endl;
    }

    // Example: Using a hypothetical function with parameters
    // (You would need to add `addNumbers` to src/lib.h and src/lib.cpp)
    // int sum = lib.addNumbers(5, 7); // Hypothetical
    // std::cout << "Sum of 5 and 7: " << sum << std::endl;
    std::cout << "Hypothetical sum of 5 and 7: " << (5+7) << std::endl;


    return 0;
}
```

To use the library, ensure your `app/CMakeLists.txt` links against `project_template_lib`:

```cmake
# app/CMakeLists.txt
# ... other configurations ...

target_link_libraries(project_template PRIVATE project_template_lib)
```
*(Note: The example functions `processData` and `addNumbers` are illustrative and would need to be implemented in the library source files.)*

## Testing

This template uses GoogleTest for unit testing.

### Enable and Build Tests

To build the tests, set the `ENABLE_TESTING` CMake option to `ON`:
```bash
cmake -S . -B build -GNinja -DENABLE_TESTING=ON
cmake --build build
```

### Run Tests

Tests can be executed in several ways:

1.  **Using CTest (recommended):**
    Navigate to your build directory and run CTest.
    ```bash
    cd build
    ctest
    ```
    Useful CTest options:
    ```bash
    ctest --rerun-failed  # Re-run only tests that failed previously
    ctest --output-on-failure # Print test output only if a test fails
    ctest -C Debug        # If using a multi-config generator
    ctest -R <test_name_regex> # Run specific tests matching a regex
    ```

2.  **Using the `--target test` CMake build option:**
    ```bash
    cmake --build build --target test
    ```
    This will compile and run all tests.

3.  **Running individual test executables:**
    Test executables are typically found in `build/test/`.
    ```bash
    ./build/test/project_template_test # Example test executable name
    ```

## Compiler Sanitizers

This project supports the use of several compiler sanitizers to help detect common bugs at runtime. Using sanitizers can significantly improve code quality and reliability.

### AddressSanitizer (ASan)
Detects memory corruption issues such as use-after-free, heap buffer overflows, stack buffer overflows, global buffer overflows, and memory leaks (with `LSAN_OPTIONS`).
Enable with CMake option: `-DENABLE_ASAN=ON`

### ThreadSanitizer (TSan)
Detects data races and other threading-related bugs in multi-threaded code. When using TSan, it's recommended to compile your entire program, including all libraries (like libstdc++), with TSan.
Enable with CMake option: `-DENABLE_TSAN=ON`
**Note:** ASan and TSan are generally mutually exclusive; you cannot enable both at the same time.

### UndefinedBehaviorSanitizer (UBSan)
Detects various types of undefined behavior, such as signed integer overflow, division by zero, misaligned pointers, and null pointer dereferences.
Enable with CMake option: `-DENABLE_UBSAN=ON`
UBSan can often be used in conjunction with ASan.

### How to Use Sanitizers

1.  **Clean your build directory** (important when changing sanitizer settings).
    ```bash
    rm -rf build
    ```
2.  **Re-run CMake** with the desired sanitizer option(s).
    ```bash
    # Example with ASan
    cmake -S . -B build -GNinja -DENABLE_ASAN=ON

    # Example with UBSan
    # cmake -S . -B build -GNinja -DENABLE_UBSAN=ON

    # Example with ASan and UBSan
    # cmake -S . -B build -GNinja -DENABLE_ASAN=ON -DENABLE_UBSAN=ON

    # If also building tests:
    # cmake -S . -B build -GNinja -DENABLE_TESTING=ON -DENABLE_ASAN=ON
    ```
3.  **Build the project.**
    ```bash
    cmake --build build
    ```
4.  **Run your application or tests.**
    ```bash
    ./build/app/project_template
    # or for tests:
    # cd build && ctest --output-on-failure
    ```
When a sanitizer detects an issue, it will print a detailed error report to standard error and typically terminate the program. This report includes information about the type of error, the location in the source code, and often a stack trace.

## Development Workflow

The project follows a library + application pattern:
- `src/` contains the core library functionality (e.g., `lib.cpp`, `lib.h`).
- `app/` contains the main application that uses the library (e.g., `main.cpp`).
- `test/` contains unit tests for the library (e.g., `test_lib.cpp`).

**To add new functionality:**
1.  Define new classes or functions in header files (`.h` or `.hpp`) in `src/`.
2.  Implement the functionality in corresponding source files (`.cpp`) in `src/`.
3.  Add unit tests for the new code in `test/`. Create new `.cpp` files for tests as needed.
4.  The CMake configuration in `src/CMakeLists.txt` and `test/CMakeLists.txt` is set up to automatically detect and compile new `.cpp` files added to these directories.
5.  If you add new public headers to `src/` that should be accessible by the application or tests, ensure they are part of the `INTERFACE` include directories in `src/CMakeLists.txt`.

## Build Performance Comparison

The template supports both Ninja and Makefiles generators. Ninja is generally faster, especially for incremental builds.

**Ninja Generator (Example):**
```bash
# Example output, actual times will vary
❯ cmake --build build
[2/2] Linking CXX executable app/project_template
# Build time: significantly faster than Makefiles for many projects
```

**Makefile Generator (Example):**
```bash
# Example output, actual times will vary
❯ cmake --build build
[100%] Linking CXX executable app/project_template
# Build time: Can be slower, especially for large projects
```
*(The original build times were specific to a small example; generalized this section.)*

## Clean Build

To remove all build artifacts and start fresh:
```bash
rm -rf build
```
Then, re-run CMake and the build command:
```bash
cmake -S . -B build -GNinja # Or your preferred generator and options
cmake --build build
```
