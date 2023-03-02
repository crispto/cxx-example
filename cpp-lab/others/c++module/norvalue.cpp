#include <iostream>
using namespace std;

class HasPtr
{
private:
        string *ptr_;
        int i_;

public:
        HasPtr(const string &c = string()) : i_(0)
        {
                cout << "default construct" << endl;
                ptr_ = new string(c);
        };
        HasPtr(HasPtr &p) : i_(p.i_)
        {
                cout << "copy " << endl;
                ptr_ = new string(*p.ptr_);
        };
        HasPtr(HasPtr &&p) : i_(p.i_)
        {
                cout << "move copy" << endl;
                ptr_ = p.ptr_;
                p.ptr_ = nullptr;
        };

        ~HasPtr()
        {
                cout << "dec construct " << *ptr_ << endl;
                delete ptr_;
        };
        void show()
        {
                if (ptr_ == nullptr) {
                        cout << "resouce moved .." << endl;
                        return;
                }
                cout << "content: " << *ptr_ << endl;
        }
};

HasPtr f()
{
        HasPtr a("helloworld");
        return a;
}

int main()
{
        // HasPtr a("hello");
        // HasPtr b(a);

        // a.show();
        // b.show();

        HasPtr c = f();
        c.show();
        return 0;
}