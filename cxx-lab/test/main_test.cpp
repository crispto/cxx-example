#include <gtest/gtest.h>
#include <vector>
#include "common.hpp"
std::vector<int> v = { 1, 3, 10, 20, 30, 5, 22 };

TEST(pico, test1)
{
  
    ASSERT_EQ(52, 52);
}

TEST(pico, test2)
{
    ASSERT_EQ(28, 72);
}
