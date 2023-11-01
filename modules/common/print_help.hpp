#ifndef __print_help__
#define __print_help__
#include <iostream>
#include <iterator>
#include <type_traits>

// TODO 如果是数字，则不输出引号
template <typename ForwardIter> void print_vec(ForwardIter begin, ForwardIter end)
{
    using value_type = typename std::iterator_traits<ForwardIter>::value_type;
    if (std::is_integral_v<value_type> || std::is_floating_point_v<value_type>) {
        while (begin != end) {
            std::cout << (*begin) << " ";
            begin++;
        }
    } else {
        while (begin != end) {
            std::cout << "\"" << (*begin) << "\""
                      << " ";
            begin++;
        }
    }
    std::cout << std::endl;
}

#endif
