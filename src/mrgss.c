/*
** mrb_mrgss.c - mrgss class
**
** Copyright (c) Manuel Quinteros 2020
**
** See Copyright Notice in LICENSE
*/
#include <mruby.h>
#include <mruby/class.h>
#include <mrgss.h>

#define MRGSS_MODULE mrb_module_get(mrb, "MRGSS")


mrb_int cap_to_byte(mrb_int value) {
    return value > 255 ? 255 : value < 0 ? 0 : value;
}

struct RClass* mrgss_module_init(mrb_state *mrb) {
    return mrb_define_module(mrb, "MRGSS");
}

struct RClass* mrgss_create_class(mrb_state *mrb, const char *name) {
    return mrb_define_class_under(mrb, MRGSS_MODULE, name, mrb->object_class);
}
