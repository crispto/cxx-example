#include <iostream>
#include <vector>

class Foo
{
    public:
    Foo(int i = 0) : id(i){};
    ~Foo()
    {
        std::cout << "foo" << id << "unde " << std::endl;
    }
    int id;
};

class A
{
    public:
    A(std::string &name_, int *feat_ = nullptr, int dim_ = 0)
            : name(name_), feat(feat_), dim(dim_){};
    ~A()
    {
        std::cout << "A " << name << " destory... " << std::endl;
        name = "";
        if (trunc && feat != nullptr)
            delete[] feat;
        dim = 0;
    };
    std::string name;
    int *feat;
    int dim;
    bool trunc = true;
    std::vector<Foo> content;
};

std::vector<A> get_A(std::vector<A> &in)
{
    std::vector<A> out;
    out.reserve(2);
    for (auto &k : in) {
        std::string new_name = k.name + "_in";
        A tmp(new_name);
        out.emplace_back(tmp);
    }
    return out;
}
int test1()
{
    std::string name = "Yang";
    std::string name2 = "Li";
    // auto a = new A(name);
    A a(name);
    A b(name2);

    std::vector<A> v;
    v.reserve(2);
    v.emplace_back(a);
    v.emplace_back(b);

    std::vector<A> new_v = get_A(v);
    std::cout << "----------------------------" << std::endl;
    for (auto nv : new_v) {
        std::cout << "name is " << nv.name << std::endl;
    }

    // v out of scope
    std::cout << a.name << std::endl;
    std::cout << "a out ot scope " << std::endl;
}

int test2()
{
    std::string name = "Yang";
    int *feat = new int[4];

    for (int i = 0; i < 4; i++) {
        feat[i] = 1;
    }
    std::cout << "feat[1] " << feat[1] << std::endl;

    A *a = new A(name, feat, 4);
    delete a;

    std::cout << "feat[1] " << feat[1] << std::endl;
}

int test3()
{
    // 一个类死亡的时候，它所管理的 vector 也会自动析构， vector 里的元素会依次析构
    std::string name = "Yang";
    int *feat = new int[4];

    for (int i = 0; i < 4; i++) {
        feat[i] = 1;
    }
    std::cout << "feat[1] " << feat[1] << std::endl;

    A *a = new A(name, feat, 4);
    a->content.emplace_back(Foo());
    a->content.emplace_back(Foo());
    std::cout << "delete a " << std::endl;
    delete a;
}

int test4()
{
    std::string name = "Yang";
    int *feat = new int[4];

    for (int i = 0; i < 4; i++) {
        feat[i] = 1;
    }
    std::cout << "feat[1] " << feat[1] << std::endl;

    A *a = new A(name, feat, 4);
    a->content.emplace_back(Foo(1));
    std::cout << "replace" << std::endl;
    a->content[0] = Foo(2);
    std::cout << "replace" << std::endl;
}

class B
{
    public:
    B(A &a_) : a(a_){};
    ~B()
    {
        a.trunc = true;
        std::cout << "B decons" << std::endl;
    };
    void show_a()
    {
        std::cout << "my a [ ";
        for (int i = 0; i < a.dim; i++) {
            std::cout << a.feat[i] << ", ";
        }
        std::cout << " ]" << std::endl;
    }

    public:
    A a;
};

int test5()
{
    int *ft = new int[4];
    for (int i = 0; i < 4; i++) {
        ft[i] = 1;
    }

    std::string name = "crispto";
    auto a = A(name, ft, 4);
    a.trunc =false;
    B b = B(a);
    b.show_a();
}

int main()
{
    test5();
}