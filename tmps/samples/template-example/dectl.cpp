#include <iostream>
#include <sstream>
using namespace std;
/*
枚举 + 模板特化
*/

template<size_t n>
struct factorial{
  enum{
    value = n * factorial<n-1>::value
  };
};

template<>
struct factorial<0>{
  enum{
    value = 1
  };
};

int main(){
  cout << factorial<5>::value << endl;
}