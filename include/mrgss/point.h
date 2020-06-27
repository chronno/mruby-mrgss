#ifndef MRUBY_MRGSS_POINT_H
#define MRUBY_MRGSS_POINT_H
#include <mruby.h>

/* Create MRuby type */
void create_point_type(mrb_state* mrb);

typedef struct mrgss_point {
    mrb_int x, y; 
} Point;

#endif