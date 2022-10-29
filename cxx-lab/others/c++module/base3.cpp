#include <iostream>

using namespace std;
// 是否会生成默认 右值拷贝构造函数
class HasPtr
{
public:
        // default constructor
        HasPtr(const string &s = string(), int i_ = 0) : ptr(new string(s)), i(i_)
        {
                arr[0] = 1;
                arr[1] = 3;
        };
        // copy constructor
        HasPtr(const HasPtr &other) : ptr(new string(*other.ptr)), i(other.i){
                arr[0] = other.arr[0];
                arr[1] = other.arr[1];
        };
        HasPtr &operator=(const HasPtr &other)
        {
                ptr = new string(*other.ptr);
                i = other.i;
                memcpy(arr, other.arr, sizeof(int) * 2);
                return *this;
        };
        bool operator <(const HasPtr &other) const{
                return i < other.i;
        }
        // HasPtr & operator=(HasPtr other){
        //         swap(*this, other);
        //         return *this;
        // }
        ~HasPtr()
        {
                delete ptr;
        };
        void show()
        {
                cout << "ptr is : " << *ptr << ", i is: " << i << ", arr is :" << arr[0] << ", "
                     << arr[1] << endl;
        };
        void set(const string &c)
        {
                *ptr = c;
        };
        friend void swap(HasPtr &p1, HasPtr &p2);

private:
        string *ptr;
        int i;
        int arr[2];
};

void swap(HasPtr &p1, HasPtr &p2){
                cout << "swap of hasptr is called " << endl;
                std::swap(p1.ptr, p2.ptr);
                std::swap(p1.i, p2.i);
                std::swap(p1.arr[0], p2.arr[0]);
                std::swap(p1.arr[1], p2.arr[1]);

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
#include <vector>
int main()
{
        HasPtr a("jack", 3);
        a.show();
        HasPtr b("bob", 2);
        HasPtr c("eric", 1);
        HasPtr d("jane", 0);

        vector<HasPtr> v{a,b,c,d};
        for (auto &x : v){
                x.show();
        }
        cout << "......................." << endl;
        sort(v.begin(), v.end());
        cout << "sor oer ............" <<endl;
        for (auto &x : v){
                x.show();
        }
        return 0;
}