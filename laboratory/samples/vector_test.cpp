#include "common.hpp"

int main() {
  int batch_size = 10;
  vector<int> a;
  a.reserve(batch_size);

  a.clear();
  cout << "A " << a.size() << endl;

  a.insert(a.end(), a.begin(), a.begin() + batch_size);
  cout << "B " << a.size() << endl;

  display(a);
}
