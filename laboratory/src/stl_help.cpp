#include <common.hpp>

class H {

} void display(vector<int> &a) {
  cout << "[";
  for (int i = 0; i < a.size(); i++) {
    if (i != a.size() - 1) {
      cout << a[i] << ", ";
    } else {
      cout << a[i] << "]" << endl;
    }
  }
}

void display(map<int, int> &m) {}