#ifndef MRUBY_MRGSS_COLOR_H
#define MRUBY_MRGSS_COLOR_H
#include <mruby.h>

/* Create MRuby type */
void create_color_type(mrb_state* mrb);

typedef struct mrgss_color {
    mrb_int r, g, b, a; 
} Color;

#endif