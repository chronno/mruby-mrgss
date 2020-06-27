#include <mruby.h>
#include <mruby/data.h>
#include <mrgss.h>
#include <mrgss/game.h>

static void mrb_game_free(mrb_state* mrb, void* data) {
    if (data) {
        Game* game = (Game*) data;
        game->mrb = NULL;
        mrb_free(mrb, game);
    }
}

static const struct mrb_data_type game_data_type = { "MRGSS::Game", mrb_game_free };

static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    Game* game;
    mrb_value screen = mrgss_instance_new(mrb, "Screen", 0, NULL);
    SET_IV("@screen", screen);
    game = mrb_malloc(mrb, sizeof(Game));
    game->game = self;
    game->mrb = mrb;
    DATA_PTR(self) = game;
    DATA_TYPE(self) = &game_data_type;
    return self;
}

static mrb_value screen_get(mrb_state* mrb, mrb_value self) {
    return GET_IV("@screen");
}

static mrb_value run(mrb_state* mrb, mrb_value self) {
    mrgss_game_start(mrb, self);
    return self;
}

void create_game_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Game");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "screen", screen_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "run", run, MRB_ARGS_NONE());
}