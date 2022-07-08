#include "andro.h"
#include "rapidjson/document.h"
#include <iostream>
using namespace rapidjson;

point_t g_center;
param create_center(const char *input) {
  // ...
  Document d;
  d.Parse(input);
  g_center.x = d["x"].GetInt();
  g_center.y = d["y"].GetInt();

}; // create a base center point
point_t add_point(point_t a, point_t b);
int cvt_point(param p, point_t *ps, int p_num,
              point_t **dst); // cvt new points with raw point
int release_data(point_t dst);

void show() {
  std::cout << "x: " << g_center.x << ", y:" << g_center.y << std::endl;
}