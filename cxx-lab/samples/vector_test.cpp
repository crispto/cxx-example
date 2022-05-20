#include "common.hpp"

int main() {
    vector<int> v(10, 1);
    display_vec(v);

    map<int, int> m;
    for (int i = 0; i < 10; i++) {
        m[i] = 2 * i;
    }
    display_map(m);
}
