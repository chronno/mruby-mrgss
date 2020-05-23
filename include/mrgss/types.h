#ifndef MRUBY_MRGSS_TYPES_H
#define MRUBY_MRGSS_TYPES_H
#include <mruby.h>
/*
 * MRuby Types Initialization
*/
void mrgss_rectangle_init(mrb_state* mrb);

/*
 * Base Structures
*/ 
typedef struct mrgss_rectangle {
    mrb_int x, y, w, h;
} MR_Rect;

typedef struct mrgss_color {
    mrb_int r, h, b, a;
} MR_Color;

typedef struct mrgss_point {
    mrb_int x, y;
} MR_Point;
#endif