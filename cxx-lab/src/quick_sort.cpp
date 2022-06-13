#include "common.hpp"
#include <fstream>
#include <json/value.h>
#include <json/json.h>

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
        Json::Reader reader;
        Json::Value content;
        std::ifstream f("param.json", std::ifstream::binary);
        std::stringstream sts;
        sts << f.rdbuf();
        reader.parse(sts.str(), content);
        std::cout << "content is " << content.asString() << std::endl;
        param.x = content["x"].asInt();
        param.y = content["y"].asInt();
        param.yaw = content["yaw"].asInt();
    }
    param.yaw += 1;
    return param;
}