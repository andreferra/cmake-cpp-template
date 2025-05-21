cmake_minimum_required(VERSION 3.14)

project(cmake-cpp-template LANGUAGES CXX C)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/StandardProjectSettings.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PreventInSourceBuilds.cmake)

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(ENABLE_TESTING "Enable Test Builds" OFF)

include_directories(include)

add_subdirectory(src)

add_subdirectory(app)

if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
