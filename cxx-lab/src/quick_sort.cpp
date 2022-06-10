#include "common.hpp"

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