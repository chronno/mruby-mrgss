#ifndef MRUBY_MRGSS_H
#define MRUBY_MRGSS_H
#include <mruby.h>
#include <mruby/data.h>
#ifndef __EMSCRIPTEN__
#include <GL/gl3w.h>
#else 
#include <emscripten/emscripten.h>
#endif
#include <GLFW/glfw3.h>
#include <mrgss/utils.h>
#include <mrgss/gl.h>
#include <mrgss/types.h>


/*
** Gem data types
*/
void create_color_type(mrb_state* mrb);
void create_point_type(mrb_state* mrb);
void create_rect_type(mrb_state* mrb);
void create_game_type(mrb_state* mrb);
void create_bitmap_type(mrb_state* mrb);
void create_sprite_type(mrb_state* mrb);
/*
**
*/
struct RClass* mrgss_module(mrb_state *mrb);
struct RClass* mrgss_class_new(mrb_state *mrb, const char *name);
struct RClass* mrgss_class_get(mrb_state *mrb, const char* name);
mrb_value mrgss_instance_new(mrb_state *mrb, const char *type, mrb_int args_count,const mrb_value *args);
mrb_bool mrgss_obj_is_a(mrb_state *mrb, mrb_value obj, const char *class_name );

/*
 * MRuby Types Initialization
*/
int create_screen(GameContext* game, mrb_int width, mrb_int height, char* title);
void show_screen(GameContext* game);
void destroy_screen(GameContext* game);

/*
**  Renderer
*/
void initialize_renderer(GameContext* game);
int prepare_renderer(GameContext* context, mrb_value batch);
void renderer_draw(GameContext* context, int renderables);

/*
** Sprite stuff
*/
void sync_sprite(mrb_state* mrb, mrb_value sprite);
#endif //MRUBY_MRGSS_H