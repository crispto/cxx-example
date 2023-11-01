#include "common/print_help.hpp"
#include "common/string.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <list>
#include <ostream>
#include <queue>
#include <utility>
using std::pair;
#define show(x) cout << x::tell() << endl;
struct split_string_ret {
    string src;
    char dim;
    unsigned int len;
};

TEST(common, split_string)
{
    vector<pair<string, char>> test_cases{ std::make_pair("", ' '), std::make_pair("hello word", ' '),
                                           std::make_pair("tom,want,to,go,there", ',') };
    for (auto &tc : test_cases) {
        auto ret = split_string(tc.first, tc.second);
        print_vec(ret.begin(), ret.end());
    }
}
struct obj {
    int age = 0;
    string name = "bobo";
};

std::ostream &operator<<(std::ostream &s, const obj &oj)
{
    s << "{name: " << oj.name << ", age: " << oj.age << "}";
    return s;
};

TEST(common, print_vec)
{

    vector<int> a{ 1, 2, 3, 4 };
    vector<float> b{ 2.0, 3.1, 4.1 };
    vector<string> c{ "if", "we", "are", "ok" };

    print_vec(a.cbegin(), a.cend());
    print_vec(b.cbegin(), b.cend());
    print_vec(c.cbegin(), c.cend());
    vector<obj> p{ { 12, "richrd" }, { 13, "cathy" } };
    print_vec(p.cbegin(), p.cend());
}
