#include <gtest/gtest.h>

#include "lib.hpp"

TEST(LibTest, InterfaceReturn)
{
    Lib lib;
    EXPECT_EQ(lib.helloWorldMsg(), "Hello World!\n");
}