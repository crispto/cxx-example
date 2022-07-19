#include <stdio.h>
#ifndef SENSEAUTO_API
#define SENSEAUTO_API extern "C" __attribute__((visibility("default")))
#endif
typedef struct point_t {
  int x;
  int y;
} point_t, *point;

typedef void *param;
SENSEAUTO_API param
create_center(const char *input); // create a base center point

SENSEAUTO_API
void free_center(param in_ptr); // create a base center point

SENSEAUTO_API
int add_point(point_t a, point_t b, point_t *out);

SENSEAUTO_API
int cvt_point(param p, point_t *ps, int p_num,
              point_t **dst); // cvt new points with raw point
int release_data(point_t dst);
SENSEAUTO_API
void show();