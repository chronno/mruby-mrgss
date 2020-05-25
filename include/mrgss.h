#include <mruby.h>
#ifndef MRUBY_MRGSS_H
#define MRUBY_MRGSS_H
/*
 * MRuby Types Initialization
*/
void mrgss_point_init(mrb_state* mrb);
void mrgss_rectangle_init(mrb_state* mrb);
void mrgss_color_init(mrb_state* mrb);
void mrgss_screen_init(mrb_state* mrb);
void mrgss_game_init(mrb_state* mrb);

#endif //MRUBY_MRGSS_H