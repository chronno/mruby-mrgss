#include <stdlib.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mrgss.h>
#include <mrgss/utils.h>
#include <mrgss/types/game.h>


static mrb_value mrgss_game_initialize(mrb_state* mrb, mrb_value self) {
    mrb_int args;
    mrb_value rect, title, fullscreen, screen;
    mrb_value screen_args[3];
    args = mrb_get_args(mrb, "oo|o", &title, &rect, &fullscreen);
    if (args == 2) { fullscreen = mrb_false_value(); } 
    if (is_string(mrb, title) && mrgss_obj_is_a(mrb, rect, "Rect") && is_boolean(mrb, fullscreen)) {
        screen_args[0] = title;
        screen_args[1] = rect;
        screen_args[2] = fullscreen;
        screen = mrgss_instance_new(mrb, "Screen", 3, screen_args);
        MRG_SET_PROP("@screen", screen);
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_TYPE_ARGS);  
        return mrb_nil_value();
    }
    return self;
}

static mrb_value mrgss_game_start(mrb_state* mrb, mrb_value self) {
    game_init(mrb, self, MRG_GET_PROP("@screen"));
    return mrb_nil_value();
}

void mrgss_game_init(mrb_state* mrb) {
    struct RClass* point = mrgss_class_new(mrb, "Game");
    mrb_define_method(mrb, point, "initialize", mrgss_game_initialize, MRB_ARGS_REQ(2)|MRB_ARGS_OPT(1));
    mrb_define_method(mrb, point, "start", mrgss_game_start, MRB_ARGS_REQ(2)|MRB_ARGS_OPT(1));
    
}