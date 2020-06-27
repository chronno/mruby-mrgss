#ifndef MRUBY_MRGSS_RECT_H
#define MRUBY_MRGSS_RECT_H
#include <mruby.h>

/* Create MRuby type */
void create_rect_type(mrb_state* mrb);

typedef struct mrgss_rect { 
    mrb_int x, y, w, h; 
} Rect;

#endif