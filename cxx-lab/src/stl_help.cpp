#include <common.hpp>

void display_vec(vector<int> &a) {
    cout << "[";
    for (int i = 0; i < a.size(); i++) {
        if (i != a.size() - 1) {
            cout << a[i] << ", ";
        } else {
            cout << a[i] << "]" << endl;
        }
    }
}

void display_map(map<int, int> &m) {
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

void display_deque(std::deque<int> &input) {
    if (input.size() == 0) {
        std::cout << "empty deque" << std::endl;
    } else {
        std::vector<int> a(input.begin(), input.end());
        display_vec(a);
    }
}