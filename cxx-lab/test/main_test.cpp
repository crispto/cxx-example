#include <gtest/gtest.h>
#include <vector>
#include "common.hpp"
std::vector<int> v = { 1, 3, 10, 20, 30, 5, 22 };
TEST(SumOfMaxNSet, POSTIVE_HANDLE)
{
    std::vector<int> v = { 1, 3, 10, 20, 30, 5, 22 };

    int ret = sum_of_max_n(v, 3);
    display_vec(v);
    ASSERT_EQ(ret, 72);
    ASSERT_EQ(sum_of_max_n(v, 2), 52);
}

TEST(SumOfMaxNSet, EXCEPT_HANDLE)
{
    std::vector<int> v = { 1, 3, 10, 20, 30, 5, 22 };

    EXPECT_NE(sum_of_max_n(v, 100), 52);
}

TEST(STLUsage, Vector)
{
    std::vector<int> v = { 1, 3, 10, 20, 30, 5, 22 };

    vector<int> output;
    int rec = vector_add(v, &output);
    display_vec(output, "stlusage");
    EXPECT_EQ(rec, 0);
    for (int i = 0; i < v.size(); i++) {
        EXPECT_EQ(v[i] * 10, output[i]);
    }
    vector<int> output2{ 2 };
    rec = vector_add(v, &output2);
    EXPECT_EQ(rec, -1);
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}