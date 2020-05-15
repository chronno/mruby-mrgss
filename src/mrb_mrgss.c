/*
** mrb_mrgss.c - mrgss class
**
** Copyright (c) Manuel Quinteros 2020
**
** See Copyright Notice in LICENSE
*/
#include <mruby.h>
#include <mruby/data.h>
#include <mrb_mrgss.h>
#include <mrgss.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

void mrb_mruby_mrgss_gem_init(mrb_state *mrb)
{
  mrgss_module_init(mrb);
  mrgss_rectangle_init(mrb);
  DONE;
}

void mrb_mruby_mrgss_gem_final(mrb_state *mrb)
{
}

