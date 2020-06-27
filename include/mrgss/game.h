#ifndef MRUBY_MRGSS_GAME_H
#define MRUBY_MRGSS_GAME_H
#include <mruby.h>
#include <mrgss.h>

/* Create MRuby type */
void create_game_type(mrb_state* mrb);

typedef struct mrgss_game {
    mrb_state* mrb;
    mrb_value game;
} Game;

void mrgss_game_start(mrb_state* mrb, mrb_value self);
#endif