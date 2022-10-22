#pragma pack(0)
#include <iostream>

// create a class, implement default, base, copy, move constructor, overload operator =, ==, <<, >>, []
using namespace std;

class Foo{
  public:
  Foo()=default;
  virtual void ShowName();

  public:
  unsigned short k;
  int* ptr;
  static const  int const_p =102;
  static int noconst_p;
};
const int Foo::const_p; // 为什么没有这句仍然可以取值，但无法取到地址
int Foo::noconst_p = 31;

void Foo::ShowName(){
  cout << "Foo base called " << endl;
}

const string a = "hello";
const string b = "world";
int main(){
  Foo f;
  cout <<"size: "<< sizeof(Foo) << endl;
  cout << "addr of f: " << &f << endl;
  cout << "addr of ptr: " << &f.ptr << endl;
  cout << "addr of k: " << &f.k << endl;
  cout << "value " << Foo::const_p << ", noconst: " << Foo::noconst_p << endl;
  cout << "addr of noconst_p: " << &(Foo::noconst_p) << endl;

  //not a good idea 
  cout << "addr of const_p: " << &(Foo::const_p) << endl;
  cout << "addr of const global var: " << "a :" << &a << ", b: " << &b<<std::endl;



  return 0;
}