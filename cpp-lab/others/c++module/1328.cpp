#include <iostream>
using namespace std;

class HasPtr
{
public:
        HasPtr(const string &s = string()) : ptr(new string(s)), i(0) { use = new int(1);};
        HasPtr(const HasPtr &h)
        {
                ptr = h.ptr;
                i = h.i;
                ++*h.use;
                use = h.use;
        };
        HasPtr &operator=(const HasPtr &h){
            if (&h == this) return *this;
            if(--*(this->use) == 0){
                delete ptr;
                delete use;
            }
            ++*h.use;
            ptr= h.ptr;
            use = h.use;
            i = h.i;
            return *this;
        };
        ~HasPtr(){
            if(--*use == 0){
                cout << "destory " << endl;
                delete ptr;
                delete use;
            }
        };
        void show(){
            cout << "use : " << *use << endl;
        }
private:
        string *ptr;
        int i;
        int *use;
};

int main(){
    HasPtr p("yang");
    p.show();
    HasPtr q = p;
    q.show();
    {
    HasPtr x(q);
    x.show();
    }

    return 0;
}