#include "andro.h"
#include "rapidjson/document.h"
#include <iostream>
using namespace rapidjson;

point g_center;
param create_center(const char *input) {
  // ...
  printf("get create_center str: %s\n", input);
  Document d;
  d.Parse(input);
  g_center = new point_t();
  g_center->x = d["x"].GetInt();
  g_center->y = d["y"].GetInt();
  std::cout << "g_center" << g_center->x << std::endl;
  return g_center;

}; // create a base center point

void free_center(param in_ptr){
  std::cout << "free center" << std::endl;
  auto q = static_cast<point>(in_ptr);
  delete q;

}
int add_point(point_t a, point_t b, point_t *o) {
  o->x = a.x + b.y;
  o->y = a.x + b.y;
  return 0;
};
int cvt_point(param p, point_t *ps, int p_num, point_t **dst) {
  point_t *base = static_cast<point_t *>(p);
  point_t *tmp = (point_t *)malloc(p_num * sizeof(point_t));
  for (int i = 0; i < p_num; i++) {
    tmp[i].x = ps[i].x + base->x;
    tmp[i].y = ps[i].y + base->y;
  }
  *dst = tmp;
  return 0;
}; // cvt new points with raw point

int release_data(point_t dst);

void show() {
  if (g_center == NULL){
    std::cout << "g_center is not inited" << std::endl;
    return;
  }
  std::cout << "x: " << g_center->x << ", y:" << g_center->y << std::endl;
}