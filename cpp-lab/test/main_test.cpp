#include <gtest/gtest.h>
#include <vector>
#include "common.hpp"
std::vector<int> v = { 1, 3, 10, 20, 30, 5, 22 };

TEST(pico, test1)
{

    ASSERT_EQ(52, 52);
}

TEST(pico, test2)
{
    ASSERT_EQ(28, 72);
}

TEST(pico, test3)
{
    int8_t data[4] = { 4, 5, 6, 7 };
    for (size_t i = 0; i < 4; i++) {
        printf("data[%ld]: %d, addr: %p\n", i, data[i], data + i);
    }
    int32_t ret = 2;
    memcpy(&ret, data, 4);
    for (size_t i = 0; i < 4; i++) {
        int8_t *p = (int8_t *)&ret + i;
        *p = data[3 - i];
        printf("ret addr: %p, value: %#x\n", p, *p);
    }
    printf("ret address %p\n", &ret);
    printf("%#x, %ld\n", ret, ret);
}

class Base
{
    protected:
    std::string name;

    public:
    virtual void info() = 0;
};

class A : public Base
{
    private:
    std::string addr;

    public:
    void info() override
    {
        printf("name: %d, addr: %s\n", name, addr);
    }
};

class B : public Base
{
    private:
    int age;
    void info() override
    {
        printf("name: %d, age: %d\n", name, age);
    }
};

typedef struct wrapper_t {
    Base *ptr;
} * wrapper;

void create_wrap(wrapper *out)
{
    wrapper x = new wrapper_t();
    x->ptr = new A();
    *out = x;
}

TEST(pico, test4)
{
    wrapper w;
    create_wrap(&w);
    Base *v = w->ptr;
    v->info();
}
