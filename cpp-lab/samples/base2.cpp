#include <iostream>
#include <assert.h>
#include <string.h>
#include <chrono>
// 探究vitural and pure vi

class BaseDoc
{
    public:
    virtual void serial() = 0;
    virtual void prompt()
    {
        std::cout << "BaseDoc::prompt" << std::endl;
    };
    void on_open()
    {
        std::cout << "BaseDoc::on_open" << std::endl;
        prompt();
        serial();
    }
};

class WordDoc : public BaseDoc
{
    public:
    virtual void prompt() override
    {
        std::cout << "WordDoc::prompt" << std::endl;
    };
    void serial() final
    {
        std::cout << "WordDoc::serial" << std::endl;
    };
};

int testInherit()
{
    WordDoc doc;
    doc.on_open();

    // 如果是一個非純虛函数呢
    // 继承类中的virtual 代表它可以被选择性 override
}

// 一个多维向量类
template <typename T> class Point
{
    public:
    Point(T v = 0.0) : _v(v){};
    T v()
    {
        return _v;
    };

    private:
    T _v;
};

template <typename T> inline std::ostream &operator<<(std::ostream &out, Point<T> &p)
{
    out << "( " << p.v() << " )";
    return out;
};

template <typename T, int dim> class Tensor
{
    public:
    Tensor(T _values[dim])
    {
        for (int i = 0; i < dim; i++) {
            values[i] = _values[i];
        }
    };
    T operator[](uint i)
    {
        assert(i < dim && 0 <= i);
        return values[i];
    }

    private:
    T values[dim];
};

template <typename T, int dim>
inline std::ostream &operator<<(std::ostream &out, Tensor<T, dim> &t)
{
    out << "( ";
    for (uint i = 0; i < dim; i++) {
        out << t[i];
        if (i != dim - 1)
            out << ", ";
    }
    out << " )";
    return out;
}

int testPoint()
{
    Point<int> a(10.0);
    std::cout << "point: " << a << std::endl;

    float raw[3] = { 3.0, 4.12, 5.68 };
    Tensor<float, 3> t(raw);
    std::cout << "tensor: " << t << std::endl;
    return 0;
}

class Material
{
    public:
    virtual void check_in()
    {
        std::cout << "Material::check_in " << std::endl;
    };
    virtual void close_conn()
    {
        std::cout << "Material::close_conn" << std::endl;
    }
    virtual void only_base_has()
    {
        std::cout << "Material::only_base_has" << std::endl;
    }
    ~Material()
    {
        std::cout << "~Material()" << std::endl;
        close_conn();
    }
};

class Book : public Material
{
    public:
    void check_in() override
    {
        std::cout << "Book::check_In" << std::endl;
    };
    void close_conn()
    {
        std::cout << "Book::close_conn" << std::endl;
    };
    ~Book()
    {
        std::cout << "~Book" << std::endl;
    }
};

int test_dynamic_binding(Material *m)
{
    m->check_in();
    m->only_base_has();
    return 0;
}

int main()
{
    Material * b1 = new Book();
    test_dynamic_binding(b1);
    std::cout << "here b1 and base class will deconstruct" << std::endl;
    delete b1;
    return 0;
}




class Foo{
    public:
    Foo(){
        std::cout <<"Foo::Foo" <<std::endl;
    }
};

class Bar{
    public:
    Bar(){
        str = "hello world";
    };
    void show(){
        std::cout << "bar content: " <<str <<std::endl;
    };
    private:
    Foo fo;
    char *str;
};

class X{
    public:
    X(){std::cout <<"X::X" << std::endl;};
    inline X(const X &x){std::cout <<"X::X_copy" << std::endl;
    memcpy(this, &x, sizeof(X)); };
    void show(){std::cout <<"X::show" << std::endl;};
};

X foo(){
    std::cout <<"into fooo" <<std::endl;
    X x;
    return x;
}
