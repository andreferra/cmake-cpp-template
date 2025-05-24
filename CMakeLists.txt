cmake_minimum_required(VERSION 3.14)

project(cmake-cpp-template LANGUAGES CXX C)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/StandardProjectSettings.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PreventInSourceBuilds.cmake)

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(ENABLE_TESTING "Enable Test Builds" OFF)

# Sanitizer Options
option(ENABLE_ASAN "Enable AddressSanitizer (ASan)" OFF)
option(ENABLE_TSAN "Enable ThreadSanitizer (TSan)" OFF)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer (UBSan)" OFF)

# Sanitizer configuration
# Ensure TSan is mutually exclusive with ASan and UBSan for this project
if(ENABLE_TSAN)
  if(ENABLE_ASAN)
    message(WARNING "AddressSanitizer (ASan) is not compatible with ThreadSanitizer (TSan). Disabling ASan.")
    set(ENABLE_ASAN OFF CACHE BOOL "Enable AddressSanitizer (ASan)" FORCE)
  endif()
  if(ENABLE_UBSAN)
    message(WARNING "UndefinedBehaviorSanitizer (UBSan) is not recommended with ThreadSanitizer (TSan) in this configuration. Disabling UBSan.")
    set(ENABLE_UBSAN OFF CACHE BOOL "Enable UndefinedBehaviorSanitizer (UBSan)" FORCE)
  endif()
endif()

if(ENABLE_ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
  # For some linkers (like LLD), you might need to add -u__asan_default_options to ensure options are linked.
  # Also, for better stack traces, you might add:
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fno-optimize-sibling-calls")
  message(STATUS "AddressSanitizer (ASan) enabled.")
endif()

if(ENABLE_TSAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")
  message(STATUS "ThreadSanitizer (TSan) enabled.")
endif()

if(ENABLE_UBSAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
  # Common UBSan flags for stricter checks / immediate exit:
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-sanitize-recover=all")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fno-sanitize-recover=all")
  message(STATUS "UndefinedBehaviorSanitizer (UBSan) enabled.")
endif()

include_directories(include)

add_subdirectory(src)

add_subdirectory(app)

if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
