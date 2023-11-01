#ifndef __COMMON_STRING__
#define __COMMON_STRING__
#include <istream>
#include <iterator>
#include <sstream>
#include <string>
#include <strstream>
#include <type_traits>
#include <utility>
#include <vector>

using std::string;
using std::vector;
template <class T> vector<string> split_string(const string &src, T dim)
{
    if (src.size() == 0) {
        return {};
    }
    std::stringstream ss(src);
    vector<string> result;
    while (1) {
        std::string tmp;
        std::getline(ss, tmp, dim);
        if (tmp.empty()) {
            break;
        }
        result.emplace_back(std::move(tmp));
    };
    return result;
}

#endif
