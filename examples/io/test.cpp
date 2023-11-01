#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int main()
{
    std::string text = "Let me split this into words";

    std::istringstream iss(text);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
    for (auto &x : results) {
        std::cout << x << std::endl;
    }
    return 0;
}
