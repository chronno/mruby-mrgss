#include <mruby.h>
#include <mrb_mrgss.h>
#include <mrgss.h>


#define DONE mrb_gc_arena_restore(mrb, 0);

void mrb_mruby_mrgss_gem_init(mrb_state *mrb) {
  mrb_define_module(mrb, "MRGSS");
  mrgss_point_init(mrb);
  mrgss_rectangle_init(mrb);
  mrgss_color_init(mrb);
  mrgss_game_init(mrb);
  mrgss_keyboard_init(mrb);
  mrgss_bitmap_init(mrb);
  mrgss_sprite_init(mrb);
  DONE;
}

void mrb_mruby_mrgss_gem_final(mrb_state *mrb) {
}