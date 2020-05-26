#include <stdlib.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mrgss.h>
#include <mrgss/utils.h>
#include <mrgss/structs.h>
#include <mrgss/types/game.h>


static const struct mrb_data_type game_data_type = {
  "MRGSS::Game", mrb_free
};

static mrb_value mrgss_game_initialize(mrb_state* mrb, mrb_value self) {
    mrb_int args, width, height;
    mrb_bool fullscreen;
    char * title;
    MR_Context* context;
    args = mrb_get_args(mrb, "zii|b", &title, &width, &height, &fullscreen);
    if (args == 2) { fullscreen = FALSE; } 
    context = mrb_malloc(mrb, sizeof(MR_Context));
    context->screen = mrb_malloc(mrb, sizeof(MR_Screen));
    context->screen->fullscreen = fullscreen;
    context->screen->width = width;
    context->screen->height = height;
    context->screen->title = title;
    context->mrb = mrb;
    context->game = self;
    DATA_PTR(self) = context;
    DATA_TYPE(self) = &game_data_type;
    return self;
}

static mrb_value mrgss_game_run(mrb_state* mrb, mrb_value self) {
    game_init(DATA_PTR(self));
    return mrb_nil_value();
}

static mrb_value mrgss_game_start(mrb_state* mrb, mrb_value self) {
    return mrb_nil_value();
}

static mrb_value mrgss_game_update(mrb_state* mrb, mrb_value self) {
    return mrb_nil_value();
}

static mrb_value mrgss_game_render(mrb_state* mrb, mrb_value self) {
    return mrb_nil_value();
}


void mrgss_game_init(mrb_state* mrb) {
    struct RClass* point = mrgss_class_new(mrb, "Game");
    mrb_define_method(mrb, point, "initialize", mrgss_game_initialize, MRB_ARGS_REQ(2)|MRB_ARGS_OPT(1));
    mrb_define_method(mrb, point, "run", mrgss_game_run, MRB_ARGS_NONE());
    mrb_define_method(mrb, point, "start", mrgss_game_start, MRB_ARGS_NONE());
    mrb_define_method(mrb, point, "update", mrgss_game_update, MRB_ARGS_NONE());
    mrb_define_method(mrb, point, "render", mrgss_game_render, MRB_ARGS_NONE());
    
}