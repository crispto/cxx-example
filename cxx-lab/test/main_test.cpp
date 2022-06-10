#include <gtest/gtest.h>
#include <vector>
#include "common.hpp"
std::vector<int> v = { 1, 3, 10, 20, 30, 5, 22 };
TEST(SumOfMaxNSet, POSTIVE_HANDLE)
{
    int ret = sum_of_max_n(v, 3);
    display_vec(v);
    ASSERT_EQ(ret, 72);
    ASSERT_EQ(sum_of_max_n(v, 2), 52);
}

TEST(SumOfMaxNSet, EXCEPT_HANDLE)
{
    EXPECT_NE(sum_of_max_n(v, 100), 52);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}