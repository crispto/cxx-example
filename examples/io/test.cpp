#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
using namespace std;

void test_array()
{
    int tmp[20]{ 0 };
    for (int i = 0; i < 20; i++) {
        std::cout << tmp[i];
        if (i == 19) {
            cout << endl;
        } else {
            cout << " ";
        }
    }
}
int main()
{
    test_array();
    std::string text = "Let me split this into words";

    std::istringstream iss(text);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
    for (auto &x : results) {
        std::cout << x << std::endl;
    }
    return 0;
}
