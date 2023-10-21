#include <common.hpp>

void display_vec(vector<int> &a, const char *msg)
{
    cout << "#####" << msg << "[";
    for (int i = 0; i < a.size(); i++) {
        if (i != a.size() - 1) {
            cout << a[i] << ", ";
        } else {
            cout << a[i] << "]" << endl;
        }
    }
}

void display_map(map<int, int> &m)
{
    cout << "{ ";
    int ind = 0;
    for (auto item : m) {
        ind++;
        cout << "\"" << item.first << "\""
             << ": ";
        cout << "\"" << item.second << "\"";
        if (ind != m.size()) {
            cout << ", ";
        } else {
            cout << " }" << endl;
        }
    }
}

void display_deque(std::deque<int> &input)
{
    if (input.size() == 0) {
        std::cout << "empty deque" << std::endl;
    } else {
        std::vector<int> a(input.begin(), input.end());
        display_vec(a);
    }
}

// 测试用vector指针来输出

int vector_add(vector<int> &input, vector<int> *output)
{
    if (output->size() != 0)
        return -1;
    for (int i = 0; i < input.size(); i++) {
        output->push_back(input[i] * 10);
    }
    return 0;
}
