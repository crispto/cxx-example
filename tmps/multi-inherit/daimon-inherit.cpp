#include <iostream>
#include <stdio.h>

using namespace std;

class Life
{
public:
    virtual void breath()
    {
        cout << "life has to breath" << endl;
    }
};

class Human : public virtual Life
{
public:
    virtual void baseFunc()
    {
        cout << "Human baseFunc " << endl;
    };
    // virtual void breath()
    // {
    //     cout << "human breath with nose" << endl;
    // }
};

class Animal : public virtual Life
{
public:
    virtual void baseFunc()
    {
        cout << "Animal baseFunc  " << endl;
    };
    virtual void breath()
    {
        cout << "animal breath with lung" << endl;
    }
};

/*
Chinese 继承 Human 和 Animal, 类中具有两个指针，因此，大小为 16
*/
class Chinese : public Animal
{
public:
    void baseFunc() override
    {
        cout << "Chinese baseFunc" << endl;
    }
};

int main()
{

    Life *ptr = new Chinese(); // 这是一个棱形继承的例子
    printf("size of ptr Chinese is  %ld\n", sizeof(Chinese));
    printf("size of a point is %ld\n", sizeof(int *));
    ptr->breath();
    return 0;
}
