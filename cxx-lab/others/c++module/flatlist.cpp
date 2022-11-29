#include <iostream>
#include <vector>
using namespace std;

class A
{
public:
        string content;
        A(string c_) : content(c_)
        {
                cout << "a constructor" << endl;
        };
        ~A()
        {
                cout << "a desconstructor : " << content << endl;
        };
};

 int main()
{
        unique_ptr<A> p1(new A("hello world"));
        cout << "string is " << p1->content << endl;
        unique_ptr<A> p2(new A("hello world2"));
        cout << "p1 is null?" << (p1 == nullptr ? 1 : 0) << endl;

        A *ptr = new A("raw ptr");
        p2.reset(ptr);
        delete p1.get();
        p1.release();
        cout << "done" << endl;
        return 0;
}