#include "andro.h"
#include <iostream>
using namespace std;

int main() {
  string a = "{\"x\": 3, \"y\": 4 }";
  show();
  create_center(a.data());
  show();
}
