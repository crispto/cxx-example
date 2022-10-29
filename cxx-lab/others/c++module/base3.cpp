#include <iostream>

using namespace std;
// 是否会生成默认 右值拷贝构造函数
class HasPtr
{
public:
        HasPtr(const string &s = string()) : ptr(new string(s)), i(0)
        {
                arr[0] = 1;
                arr[1] = 3;
        };
        HasPtr(const HasPtr &other) : ptr(new string(*other.ptr)), i(other.i){};
        HasPtr &operator=(const HasPtr &other)
        {
                ptr = new string(*other.ptr);
                i = other.i;
                memcpy(arr, other.arr, sizeof(int) * 2);
                return *this;
        };
        ~HasPtr()
        {
                delete ptr;
        }
        void show()
        {
                cout << "ptr is : " << *ptr << ", i is: " << i << ", arr is :" << arr[0] << ", "
                     << arr[1] << endl;
        }
        void set(const string &c)
        {
                *ptr = c;
        }

private:
        string *ptr;
        int i;
        int arr[2];
};

int i = 0;
class numbered
{
public:
        numbered() : v2(10)
        {
                mysn = i++;
                cout << "default const" << endl;
        };
        //  numbered(const numbered &other){mysn = i++; cout << "copy const" << endl;};
        //  numbered & operator=(const numbered &other){mysn = other.mysn; cout << "copy operator"
        //  << endl;return *this;};
        void show()
        {
                cout << "mysn :" << mysn << endl;
        };
        int mysn;
        const int v2;
};
void f(const numbered &s)
{
        cout << "mysn: " << s.mysn << endl;
};
int main()
{
        // numbered a, b = a, c = b;
        numbered a;
        numbered b = a;
        numbered c = b;
        // b =a ;
        // c =b;
        a.show();
        b.show();
        c.show(); 
        // f(a); f(b); f(c);

        return 0;
}