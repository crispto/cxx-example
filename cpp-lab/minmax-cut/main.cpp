#include "cut.hpp"
#include "km.hpp"

#include <vector>
#include <iostream>

using namespace std;

vector<vector<vector<int>>> tests;
void pre()
{
    // 1, 2, 0
    tests.push_back({
        { 25, 40, 35 },
        { 40, 60, 35 },
        { 20, 40, 25 },
    });
    // 1, 2, 0
    tests.push_back({
        { 64, 18, 75 },
        { 97, 60, 24 },
        { 87, 63, 15 },
    });

    // 3, 2, 1, 0
    tests.push_back({
        { 80, 40, 50, 46 },
        { 40, 70, 20, 25 },
        { 30, 10, 20, 30 },
        { 35, 20, 25, 30 },
    });
    // 0,2,3,-1, 1,
    tests.push_back({
        { 10, 19, 8, 15 },
        { 10, 18, 7, 17 },
        { 13, 16, 9, 14 },
        { 12, 19, 8, 18 },
        { 14, 17, 10, 19 },
    });
};
template <typename T> static void display_vec(T &&input)
{
    for (size_t i = 0; i < input.size(); i++) {
        cout << input[i];
        if (i < input.size() - 1) {
            cout << ", ";
        } else {
            cout << endl;
        }
    }
}

#include <algorithm>
#include <set>
#include <vector>
std::vector<int> runMatch2(std::vector<std::vector<float>> &mat, float thresh = 45.f)
{
    std::vector<int> ret(mat.size(), -1);
    const float thresh_inc = 2.0;
    // 行小于列，则行优先选取
    std::set<int> choiced;
    // 对不同的阈值先循环， 优先找小的。
    for (float dis = 1.f; dis < thresh; dis += thresh_inc) {
        // 选到了， 直接下一行
        for (size_t i = 0; i < mat.size(); i++) {

            if (ret[i] != -1) {
                continue; // 在上一个 dis 中已经成功匹配
            }
            // 最小值已经超过阈值，直接放弃本次设置该行
            if (*std::min_element(mat[i].cbegin(), mat[i].cend()) > dis) {
                break;
            }
            for (size_t j = 0; j < mat[0].size(); j++) {
                if (mat[i][j] <= dis && choiced.count(j) == 0) {
                    printf("i:%ld, j: %ld, dis: %f\n", i, j, mat[i][j]);
                    ret[i] = j;
                    choiced.insert(static_cast<int>(j));
                    break;
                }
            }
        }
        // 提前找完
        if (choiced.size() == mat.size() || choiced.size() == mat[0].size()) {
            break;
        }
    }
    return ret;
}

static void format_assign(vector<int> &result, int row_num, int col_num)
{
    vector<int> ret(row_num + col_num);
    for (size_t i = 0; i < ret.size(); i++) {
        ret[i] = result[i + 1] - row_num - 1;
    }
    display_vec(ret);
}

void test_one_matrix(vector<vector<float>> &mat)
{
    auto ret = runMatch2(mat);
    display_vec(ret);
    cout << "------------------------" << endl;
}

static vector<int> hungrian_output_to_vec(vector<vector<int>> &input)
{
    vector<int> ret(input.size(), -1);
    for (size_t i = 0; i < input.size(); i++) {
        for (size_t j = 0; j < input[0].size(); j++) {
            if (input[i][j] == 1) {
                ret[i] = j;
            }
        }
    }
    return ret;
}

static vector<vector<float>> to_float(vector<vector<int>> &intMatrix)
{
    std::vector<std::vector<float>> floatMatrix;
    // Resize the floatMatrix to match the dimensions of the intMatrix
    floatMatrix.resize(intMatrix.size());
    for (size_t i = 0; i < intMatrix.size(); ++i) {
        floatMatrix[i].resize(intMatrix[i].size());
    }

    // Convert and copy the values from intMatrix to floatMatrix
    for (size_t i = 0; i < intMatrix.size(); ++i) {
        for (size_t j = 0; j < intMatrix[i].size(); ++j) {
            floatMatrix[i][j] = static_cast<float>(intMatrix[i][j]);
        }
    }
    return floatMatrix;
}
int main()
{
    using namespace Munkres;
    pre();
    for (auto &mat : tests) {
        auto float_mat = to_float(mat);
        test_one_matrix(float_mat);
    }

    // cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    // for (auto &mat : tests) {
    //     auto ret = hungarian(mat);
    //     display_vec(hungrian_output_to_vec(ret));
    // }
}