#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main(){
    vector<int> vec1 = {1,2};
    vector<int> vec2 = {1};
    auto b = equal(vec1.cbegin(), vec1.cend(), vec2.cbegin());
    cout << b << endl;
}