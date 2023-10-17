#include <iostream>
#include <stdio.h>

using namespace std;

class Human
{
    public:
    virtual void baseFunc()
    {
        cout << " this is Human baseFunc " << endl;
    }
};

class Animal
{
    public:
    virtual void baseFunc()
    {
        cout << " this is Animal baseFunc  " << endl;
    }
};

class Chinese : public Human
{
    public:
    void baseFunc() override
    {
        cout << "this is Chinese baseFunc" << endl;
    }
};

int main()
{

    Human *ptr = new Chinese();
    printf("size of ptr Chinese is  %ld\n", sizeof(Chinese));
    printf("size of a point is %ld\n", sizeof(int *));
    ptr->baseFunc();
    return 0;
}

/*
Chinese 只继承 Human, 则只有一个续表指针，因此，大小为 8
*/