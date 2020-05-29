#include <mruby.h>
#include <mrgss/structs.h>
#ifndef MRUBY_MRGSS_H
#define MRUBY_MRGSS_H
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
void renderer_draw(GameContext* context);

/*
** Sprite stuff
*/
void sync_sprite(mrb_state* mrb, mrb_value sprite);
#endif //MRUBY_MRGSS_H