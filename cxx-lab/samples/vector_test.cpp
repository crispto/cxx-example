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


void accept_string(const std::string & input){
  std:cout << "input is " << input << std::endl;
}

void accept_char(const char* input){
  accept_string(std::string(input));
}

int main()
{
  const char * v = "yangcheng";
  accept_char(v);
}
