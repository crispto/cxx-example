#include <iostream>
// 手工实现共享指针

// todo  增加线程安全
// 解决循环引用问题
// 补充其他运算符和函数
class my_shared_ptr
{
public:
        my_shared_ptr() : data(nullptr), use_count(nullptr)
        {
                std::cout << "default is called" << std::endl;
        }; // 默认构造
        my_shared_ptr(int *ptr); //  基本构造
        my_shared_ptr(const my_shared_ptr &other); // 拷贝构造
        my_shared_ptr &operator=(const my_shared_ptr &other); // 拷贝赋值运算符
        void test(const my_shared_ptr &other);
        ~my_shared_ptr();

        void string()
        {
                if (data == nullptr || use_count == nullptr)
                        std::cout << "empty point" << std::endl;
                else
                        std::cout << "data is " << *data << ", use_count: " << *use_count
                                  << std::endl;
        }

private:
        int *data;
        int *use_count;
};

my_shared_ptr::my_shared_ptr(int *ptr) : data(ptr)
{
        use_count = new int(1);
}

my_shared_ptr::my_shared_ptr(const my_shared_ptr &other)
{
        data = other.data; // 为什么这里能访问private 变量
        use_count = other.use_count;
        *(other.use_count) += 1;
        std::cout << "copy construct is called" << std::endl;
}

// 这个比较复杂
my_shared_ptr &my_shared_ptr::operator=(const my_shared_ptr &other)
{
        std::cout << "copy assign operator is called" << std::endl;
        // 1. &other == this
        if (&other == this)
                return *this;
        // 2. this 共享的那个指针需要被减1甚至析构掉
        *this->use_count -= 1;
        // std::cout <<"use_count is " << *this->use_count << std::endl;
        if (*this->use_count == 0) {
                std::cout << "data removed " << *this->data << std::endl;
                delete this->data;
        }
        data = other.data;
        use_count = other.use_count;
        *(other.use_count) += 1;
        return *this;
}
my_shared_ptr::~my_shared_ptr()
{
        *use_count -= 1;
        if (*use_count == 0) {
                std::cout << "final remove data " << *data << std::endl;
                delete data;
				delete use_count;
        }
}

int main()
{
        int *r = new int(10);
        my_shared_ptr a(r);
        a.string();

        my_shared_ptr b(a);
        b.string();

        my_shared_ptr c(b);
        c.string();
        a.string();
        b.string(); // 3

        my_shared_ptr x(new int(20));
        my_shared_ptr y(x);
        y.string();
        y = c; // 当心内存泄露
        x.string(); // 1
        y.string(); // 4

        my_shared_ptr z(new int(30));
        z.string();
        z = y;
        z.string(); // 5 & int(30)will be delete

        return 0;
}