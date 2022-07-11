#include "common.hpp"

int test_vec()
{
    vector<int> v(10, 1);
    display_vec(v);

    map<int, int> m;
    for (int i = 0; i < 10; i++) {
        m[i] = 2 * i;
    }
    display_map(m);
    return 0;
}
void test_call()
{
    for (int i = 0; i < 10; i++) {
        cam_param_t v = call_counter();
        std::cout << "x " << v.x << " y: " << v.y << "yaw: " << v.yaw << std::endl;
    }
}

void accept_string(const std::string &input)
{
    std::cout << "input is " << input << std::endl;
};

void accept_char(const char *input)
{
    accept_string(std::string(input));
}

void test_getstring()
{
    std::string input = "hello";
    char *out = get_char_array(input);
    std::cout << "out is  " << out << std::endl;
    std::cout << "len of the str is " << strlen(out) << std::endl;
    delete[] out;
}

void test_getstring2()
{
    std::string input = "hello";

    char out[1025];
    int ret = get_char_array2(input, out);
    if (ret < 0) {
        std::cout << "error" << std::endl;
        return;
    }
    std::cout << "out is " << out << "\nlen of out is " << strlen(out) << std::endl;
}
int test3()
{
    const char *v = "yangcheng";
    accept_char(v);
    return 0;
}

int main()
{
    test_getstring2();
    return 0;
}