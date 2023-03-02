#include <iostream>
#include <assert.h>
#include <string.h>
#include <ctime>
#include <chrono>
// 探究vitural and pure virtual

class test
{
    friend test foo(double);
    // friend operator=(test& this, test& other);

    public:
    test()
    {
        std::cout << "test default constructor called " << std::endl;
        memset(array, 0, 100 * sizeof(double));
    };
    test(const test &x)
    {
        std::cout << "copy construct is called" << std::endl;
        memcpy(this, &x, sizeof(test));
    }
    test &operator=(const test &src)
    {
        std::cout << "assign construct is called" << std::endl;

        memcpy(this, &src, sizeof(test));
    };
    void show()
    {
        std::cout << "local: " << array[0] << ", " << array[1] << ", "
                  << "...." << array[99] << std::endl;
    }

    private:
    double array[100];
};

test foo(double val)
{
    test local;
    local.array[0] = val;
    local.array[99] = val;
    return local;
};

int64_t timecut()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    return ms.count();
}

int main()
{
    int64_t start = timecut();
    for (int i = 0; i < 10000; i++) {
        // std::cout <<"i ... " <<i <<std::endl; 
        test k = foo(float(i));
        k.show();
    }
    int64_t end = timecut();
    std::cout << "time escap: " << end - start << std::endl;
}