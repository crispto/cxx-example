#include "iostream"

/* vector 的 iter 构造是否是 move 的

/  g++ -fsanitize=address -g ./main.cpp -o main
    结论： vec  的 iter 构造方式并不是 move 的，而是 copy 的
*/

#include <vector>

using namespace std;

void change_int(int *a)
{
    *a = *a + 1;
    cout << "in change_int " << *a << endl;
}

int main()
{

    const int a = 11;
    const int  *p = &a;
    cout <<"p is " << *p << endl;
    // const_cast 确实可以把一个 const int * 转换为 int* 的形参中，
    // 但是这个过程中，外部的const 仍然是不可更改的
    change_int(const_cast<int*>(p));
    cout << "a " << a << endl;

    int x = 22;
    change_int(&x);
    cout << "x is " << x << endl;
}
