#include "andro.h"
#include <iostream>
using namespace std;

int main() {
  string a = "{\"x\": 3, \"y\": 4 }";
  show();
  void * p = create_center(a.data());
  show();
  point_t p1{x : 3, y : 4};
  point_t p2{x : 3, y : 6};
  point_t p3;
  add_point(p1, p2, &p3);
  std::cout << "x: " << p3.x << " , " << p3.y << std::endl;
  
  free_center(p);
  show();
}
