#include <stdio.h>

typedef struct point_t {
  int x;
  int y;
} point_t, *point;

typedef void *param;
param create_center(const char *input); // create a base center point
point_t add_point(point_t a, point_t b);
int cvt_point(param p, point_t *ps, int p_num,
              point_t **dst); // cvt new points with raw point
int release_data(point_t dst);
void show();