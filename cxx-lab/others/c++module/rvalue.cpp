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
        Foo( Foo &&r)
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

int main()
{
   Foo k(std::move(f()));
   return 0;
}