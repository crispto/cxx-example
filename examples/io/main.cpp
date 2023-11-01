#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;
#define PI 3.141592654

void execute(vector<function<void()>> &tasks)
{
    for (auto &f : tasks) {
        f();
    }
}

void foo()
{
    cout << "foo is called" << endl;
}

struct bob {
    void operator()()
    {
        cout << "bob() is called " << endl;
    }
};

class Nes
{
public:
    Nes(const string &name) : name_(name){};

    static int peak(int i, float j)
    {
        cout << "Nes::peak is called" << endl;
        return 1;
    };
    void eat(int k)
    {
        cout << "Nes.eat is called "
             << "name: " << name_ << "k is " << k << endl;
    }

private:
    string name_;
};

void show(int i, float j)
{
    cout << "i is " << i << endl;
    cout << "j is " << j << endl;
}

int main()
{
    vector<function<void()>> que;
    Nes ne{ "li" };
    Nes ne2{ "go" };
    que.emplace_back([] { foo(); });
    que.emplace_back(bob{});
    que.emplace_back([] { Nes::peak(1, 0.2); });
    int i = 12;
    que.emplace_back([&]() { bind(&Nes::eat, &ne, placeholders::_1)(i); });
    que.emplace_back(bind(&Nes::eat, &ne2, 10));
    execute(que);

    function<void(float, int)> bind_show = bind(show, placeholders::_2, placeholders::_1); 
    bind_show(1.20, 3);
    show(4, 1.2);
}
