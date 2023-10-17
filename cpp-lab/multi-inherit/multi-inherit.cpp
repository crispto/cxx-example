#include <iostream>
#include <stdio.h>

using namespace std;

class Human
{
    public:
    virtual void baseFunc()
    {
        cout << "Human baseFunc " << endl;
    }
};

class Animal
{
    public:
    virtual void baseFunc()
    {
        cout << "Animal baseFunc  " << endl;
    }
};

/*
Chinese 继承 Human 和 Animal, 类中具有两个指针，因此，大小为 16
*/
class Chinese : public Human, public Animal
{
    public:
    void baseFunc() override
    {
        cout << "Chinese baseFunc" << endl;
    }
};

int main()
{

    Human *ptr = new Chinese();
    printf("size of ptr Chinese is  %ld\n", sizeof(Chinese));
    printf("size of a point is %ld\n", sizeof(int *));
    ptr->baseFunc();

    // 可以手动指定调用父类的函数
    ptr->Human::baseFunc();
    return 0;
}
