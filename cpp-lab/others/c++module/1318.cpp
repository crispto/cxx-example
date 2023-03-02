#include <iostream>

using namespace std;

class Employee
{
public:
        Employee(const string &name = string()) : name_(name)
        {
                id_ = Employee::id++;
        };
        Employee(const Employee &other) : name_(other.name_)
        {
                id_ = Employee::id++;
                cout << "copy const called " << endl;
        };
        Employee &operator=(const Employee &other)
        {
                name_ = other.name_;
                id_ = Employee::id++;
                cout << "copy operator called " << endl;
                return *this;
        };

public:
        void show()
        {
                cout << "{ name_: " << name_ << ", id_: " << id_ << " }" << endl;
        };

private:
        string name_;
        int id_;
        static int id;
};

int Employee::id = 100;

int main()
{
        //         Employee jack("jack");
        //         jack.show();

        //         Employee bob;
        //         bob = jack;
        //         bob.show();
        cout << "size of int " << sizeof(int) << std::endl;
        cout << "size of ptr" << sizeof(int*) << endl;
        return 0;
}