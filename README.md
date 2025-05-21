# C++ CMake Project Template

A modern C++ project template using CMake for building applications with integrated testing support.

## Project Structure

```
├── app/                 # Main application
├── src/                 # Library source code
├── test/                # Unit tests (GoogleTest)
├── cmake/               # CMake utility scripts
└── CMakeLists.txt       # Root CMake configuration
```

## Quick Start

### Basic Build

```bash
cmake -S . -B build
cmake --build build
```

### Recommended Build (with Ninja)

For faster build times, use Ninja as the CMake generator:

```bash
cmake -S . -B build -GNinja
cmake --build build
```

### Running the Application

After building, the executable will be located at:
```bash
./build/app/project_template
```

## Testing

### Enable and Build Tests

```bash
cmake -S . -B build -DENABLE_TESTING=ON
cmake --build build
```

### Run Tests

```bash
# Run all tests
cmake --build build --target test

# Or using CTest directly
cd build
ctest

# Useful CTest options
ctest --rerun-failed --output-on-failure
```

## Build Configuration Options

| Option | Description | Default |
|--------|-------------|---------|
| `ENABLE_TESTING` | Enable building test applications | `OFF` |
| `WARNINGS_AS_ERRORS` | Treat compiler warnings as errors | `OFF` |

### Example with Options

```bash
cmake -S . -B build -DENABLE_TESTING=ON -DWARNINGS_AS_ERRORS=ON
cmake --build build
```

## Build Performance Comparison

The template supports both Ninja and Makefiles generators. Here's a performance comparison:

**Ninja Generator:**
```bash
❯ cmake --build build
[0/2] Re-checking globbed directories...
[14/14] Linking CXX executable test/project_template_test
# Build time: ~8s
```

**Makefile Generator:**
```bash
❯ cmake --build build
[  7%] Building CXX object src/CMakeFiles/project_template_lib.dir/lib.cpp.o
[ 14%] Linking CXX static library libproject_template_lib.a
# ... (more verbose output)
[100%] Linking CXX static library ../../../lib/libgmock_main.a
# Build time: ~13s
```

## Features

- **Modern C++17** standard
- **Modular structure** with separate library and application
- **Integrated testing** with GoogleTest
- **Build optimization** with ccache support
- **Cross-platform** compatibility
- **Out-of-source builds** enforced
- **Compile commands** generation for IDE support

## Requirements

- CMake 3.14 or higher
- C++17 compatible compiler
- Optional: Ninja build system for faster builds
- Optional: ccache for build caching

## Development

The project follows a library + application pattern:
- `src/` contains the core library functionality
- `app/` contains the main application that uses the library
- `test/` contains unit tests for the library

To add new functionality:
1. Add source files to `src/`
2. Add corresponding tests to `test/`
3. The CMake configuration will automatically detect new files

## Clean Build

To start fresh:
```bash
rm -rf build
cmake -S . -B build -GNinja
cmake --build build
```
