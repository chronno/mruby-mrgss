/*
**
** Copyright (c) Manuel Quinteros 2020
**
** See Copyright Notice in LICENSE
*/
#ifndef MRB_MRGSS_H
#define MRB_MRGSS_H
#include <mruby.h>

/*
**  Gem Structured Files
*/
void mrb_mruby_mrgss_gem_init(mrb_state *mrb);
void mrb_mruby_mrgss_gem_final(mrb_state *mrb);

/*
** Gem data types
*/
void create_color_type(mrb_state* mrb);
void create_point_type(mrb_state* mrb);
void create_rect_type(mrb_state* mrb);
void create_game_type(mrb_state* mrb);
void create_bitmap_type(mrb_state* mrb);
void create_sprite_type(mrb_state* mrb);
#endif
