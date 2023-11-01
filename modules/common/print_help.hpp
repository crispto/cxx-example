#ifndef __print_help__
#define __print_help__
#include <iostream>
#include <iterator>
#include <type_traits>

template <typename ForwardIter> void print_vec(ForwardIter begin, ForwardIter end)
{
    using value_type = typename std::iterator_traits<ForwardIter>::value_type;
    std::string sep = "\"";
    // 整数和浮点数就不用加引号
    if (std::is_integral_v<value_type> || std::is_floating_point_v<value_type>) {
        sep = "";
    }
    std::cout << "[";
    while (begin != end) {
        std::cout << sep << (*begin) << sep;
        if (begin + 1 != end) {
            std::cout << ", ";
        }
        begin++;
    }
    std::cout << "]" << std::endl;
}

#endif
