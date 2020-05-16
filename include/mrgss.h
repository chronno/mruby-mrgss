/*
** mrb_mrgss.c - mrgss class
**
** Copyright (c) Manuel Quinteros 2020
**
** See Copyright Notice in LICENSE
*/
#ifndef MRUBY_MRGSS_CORE_MRGSS_H
#define MRUBY_MRGSS_CORE_MRGSS_H

#include <mruby.h>

//UTIL
static const char* WRONG_NUMBER_ARGS = "Wrong number of arguments";
struct RClass* mrgss_module_init(mrb_state *mrb);
struct RClass* mrgss_create_class(mrb_state *mrb, const char *name);
mrb_int cap_to_byte(mrb_int value);
//RUBY TYPES
void mrgss_rectangle_init(mrb_state* mrb);
void mrgss_color_init(mrb_state *mrb);

//Initializers
mrb_value create_rectangle_from(mrb_state* mrb, mrb_int x, mrb_int y, mrb_int width, mrb_int height);
mrb_value create_color_from(mrb_state* mrb, mrb_int x, mrb_int y, mrb_int width, mrb_int height);

#endif //MRUBY_MRGSS_CORE_MRGSS_H