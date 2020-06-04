#include <mrgss.h>

static void game_free(mrb_state *mrb, void *p) {
    if (p) {
        GameContext* context = (GameContext*) p;
        destroy_screen(context);
        context->mrb = NULL;
        context->game = mrb_nil_value();
        mrb_free(mrb, context);
    }
}

struct mrb_data_type const game_data_type = {"MRGSS::Game", game_free};

static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    mrb_int w, h;
    char* title;
    GameContext* game;
    mrb_value renderer;
    mrb_value rendererArgs[2];
    mrb_get_args(mrb, "iiz", &w, &h, &title);
    MRG_SET_PROP("@width", mrb_fixnum_value(w));
    MRG_SET_PROP("@height", mrb_fixnum_value(h));
    MRG_SET_PROP("@title", mrb_str_new_cstr(mrb, title));
    game = mrb_malloc(mrb, sizeof(GameContext));
    game->game = self;
    game->mrb = mrb;
    if (create_screen(game, w,h,title)) {
        rendererArgs[0] = mrb_fixnum_value(w);
        rendererArgs[1] = mrb_fixnum_value(h);
        renderer = mrgss_instance_new(mrb, "Viewport", 2, rendererArgs);
        MRG_SET_PROP("@viewport", renderer);
        DATA_TYPE(self) = &game_data_type;
        DATA_PTR(self) = game;
    } else {
        mrb_free(mrb, game);
        mrb_raise(mrb, E_RUNTIME_ERROR, "Couldn't start the game");
    }
    return self;
}


static mrb_value run(mrb_state* mrb, mrb_value self) {
    show_screen(DATA_PTR(self));
    return self;
}

static mrb_value get_viewport(mrb_state* mrb, mrb_value self) {
    return MRG_GET_PROP("@viewport");
}

void create_game_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Game");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, type, "run", run, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, type, "viewport", get_viewport, MRB_ARGS_NONE());
}