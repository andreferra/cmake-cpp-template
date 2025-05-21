add_definitions(-DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest/
        GIT_TAG v1.17.0)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
        ON
        CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES_TEST_LIST CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(TEST_NAME ${CMAKE_PROJECT_NAME}_test)
add_executable(${TEST_NAME} ${SOURCES_TEST_LIST})
target_link_libraries(${TEST_NAME} ${CMAKE_PROJECT_NAME}_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
