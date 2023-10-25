
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void func_call()
{
    static int a = 100;
    a += 1;
    cout << "a " << a << endl;
}
int main()
{
    std::vector<int> a{ 3, 1, 2 };
    std::sort(a.begin(), a.end());
    for (auto const &iter : a) {
        cout << iter << endl;
    }
    for (auto iter = a.begin(); iter != a.end(); iter++) {
        cout << *iter << endl;
    }
    return 0;
}
