#include <iostream>
#include <vector>
using namespace std;

class Foo
{
public:
        Foo()
        {
                cout << "default cons" << endl;
        };
        Foo(const Foo &r)
        {
                cout << "copy const " << endl;
                data = r.data;
        };
        Foo(Foo &&r)
        {
                cout << "right copy const" << endl;
                data = std::move(r.data);
        }

private:
        string data;
};

Foo f()
{
        Foo x;
        return x;
};

void f1(Foo &x)
{
        cout << "left " << endl;
};
void f1(Foo &&x)
{
        cout << "right" << endl;
};

int main()
{
        //    Foo k(std::move(f()));
        Foo a;
        f1(a);
        // f1(f());
        Foo && v = std::move(a);
        f1(v);
        return 0;
}