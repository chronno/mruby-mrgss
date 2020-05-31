#include <mrgss.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

void mrb_mruby_mrgss_gem_init(mrb_state *mrb) {
  mrb_define_module(mrb, "MRGSS");
  create_color_type(mrb);
  create_point_type(mrb);
  create_rect_type(mrb);
  create_game_type(mrb);
  create_bitmap_type(mrb);
  create_sprite_type(mrb);
  DONE;
}

void mrb_mruby_mrgss_gem_final(mrb_state *mrb) {
}