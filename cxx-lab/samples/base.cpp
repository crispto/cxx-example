#include <iostream>
#include <assert.h>
// 探究vitural and pure virtual 
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

template<typename T>
inline std::ostream& operator << (std::ostream & out, Point<T> & p){
    out << "( " << p.v() << " )";
    return out;
};

template<typename T, int dim> class Tensor{
    public:
    Tensor( T _values[dim]){
        for (int i =0 ;i< dim;i++){
            values[i] = _values[i];
        }
    };
    T operator [](uint i){
        assert (i < dim && 0 <=i);
        return values[i];
    }

    private:
    T values[dim];


};

template<typename T, int dim>
inline std::ostream& operator <<(std::ostream &out, Tensor<T, dim> &t){
    out << "( ";
    for (uint i = 0;i <dim;i++){
        out << t[i];
        if (i != dim -1)
            out <<", ";
    }
    out <<" )";
    return out ;
}

int main(){
    Point<int> a(10.0);
    std::cout <<"point: " << a <<std::endl;

    float raw[3] = {3.0, 4.12, 5.68};
    Tensor<float, 3> t(raw);
    std::cout << "tensor: " << t <<std::endl;
    return 0;
}