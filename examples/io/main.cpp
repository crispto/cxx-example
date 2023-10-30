#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;
#define PI 3.141592654

float cal_degree(float x, float y)
{
    float angle_deg = std::atan2(y, x) * 180 / PI;
    if (angle_deg < 0) {
        angle_deg = 360 + angle_deg;
    }
    return angle_deg;
}

int main()
{
    vector<pair<float, float>> vec{ { 1.2, 1.3 }, { -3.2, 3.3 }, { -3.2, -1.45 }, { 3.4, -1.5 } };
    for (auto &x : vec) {
        float deg = cal_degree(x.first, x.second);

        cout << "degrees is " << deg << endl;
    }

    return 0;
}
