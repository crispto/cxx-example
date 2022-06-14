#ifndef __COMMON_HEADER__
#define __COMMON_HEADER__
#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "json.hpp"
using namespace std;

void display_vec(vector<int> &a, const char *msg = " ");
void display_map(map<int, int> &a);
void display_deque(std::deque<int> &input);
int sum_of_max_n(std::vector<int> &input, int num);
int vector_add(vector<int> &input, vector<int> *output);

typedef struct cam_param_t {
    int x = 0;
    int y = 0;
    int yaw = 0;
} cam_param_t;

cam_param_t call_counter();
// 获取一个 upper case 的char数组
char *get_char_array(const std::string &init_str); // 需要调用者手动释放
int get_char_array2(const std::string &init_str, char out[1024]); // 简单的实现
#endif
