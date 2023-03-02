#include <string>
#include "common.hpp"
char *get_char_array(const std::string &init_str)
{
    char *ch = new char[init_str.size() + 1];
    init_str.copy(ch, init_str.size());
    ch[init_str.size()] = '\0';
    return ch;
}

int get_char_array2(const std::string &init_str, char out[1024])
{
    if (init_str.size() >= 1024)
        return -1;
    init_str.copy(out, init_str.size());
    std::copy(init_str.begin(), init_str.end(), out);
    int s = init_str.size();
    out[s] = '\0';
    for (int i = 0; i < s; i++) {
        if ('a' <= out[i] && out[i] <= 'z')
            out[i] += 'A' - 'a';
    }
    std::cout << "xx" << std::endl;
    return s;
}
