#include "common.hpp"
#include <fstream>
int sum_of_max_n(std::vector<int> &input, int num)
{
    for (int i = 0; i < input.size(); i++) {
        for (int j = input.size() - 1; j > i; j--) {
            if (input[i] < input[j]) {
                int tmp = input[i];
                input[i] = input[j];
                input[j] = tmp;
            }
        }
    }
    int total = 0;
    for (int x = 0; x < num; x++) {
        total += input[x];
    }
    return total;
}

cam_param_t call_counter()
{
    static int inited = 0;
    static cam_param_t param;
    if (!inited) {
        std::ifstream i("param.json");
        nlohmann::json content;
        i >> content;
        std::cout << "content is " << content << std::endl;
        param.x = content["x"];
        param.y = content["y"];
        param.yaw = content["yaw"];
        inited = 1;
    }
    param.yaw += 1;
    return param;
}