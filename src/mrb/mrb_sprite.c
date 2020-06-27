#include <mruby.h>
#include <mruby/data.h>
#include <mruby/array.h>
#include <mrgss.h>
#include <mrgss/sprite.h>

static void mrb_sprite_free(mrb_state* mrb, void* data) {
    if (data) {
        Sprite* sprite = (Sprite*) data;
        mrb_free(mrb, sprite->position);
        mrb_free(mrb, sprite->origin);
        mrb_free(mrb, sprite->zoom);
        mrb_free(mrb, sprite->src_rect);
        mrb_free(mrb, sprite);
    }
}

static const struct mrb_data_type sprite_data_type = { "MRGSS::Sprite", mrb_sprite_free };


static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    Game* game;
    Sprite* sprite;
    mrb_value viewp;
    mrb_int argc;
    argc = mrb_get_args(mrb, "|o", &viewp);
    if (argc == 1) {
        if (!is_a(mrb, viewp, "Viewport")) {
            mrb_raise(mrb, E_ARGUMENT_ERROR, "wanted a viewport");
            return mrb_nil_value();
        }
    } else {
        game = getContext();
        viewp = GET_IV_FROM(GET_IV_FROM(game->game, "@screen") , "@viewport");
    }
    sprite = mrb_malloc(mrb, sizeof(Sprite));
    sprite->angle = 0;
    sprite->position = mrb_malloc(mrb, sizeof(Point));
    sprite->position->x = 0;
    sprite->position->y = 0;
    sprite->zoom = mrb_malloc(mrb, sizeof(Point));
    sprite->zoom->x = 1;
    sprite->zoom->y = 1;
    sprite->origin = mrb_malloc(mrb, sizeof(Point));
    sprite->origin->x = 0;
    sprite->origin->y = 0;
    sprite->src_rect = mrb_malloc(mrb, sizeof(Rect));
    sprite->src_rect->x = 0;
    sprite->src_rect->y = 0;
    sprite->src_rect->w = 20;
    sprite->src_rect->h = 20;
    SET_IV("@viewport", viewp);
    mrb_ary_push(mrb, GET_IV_FROM(viewp, "#drawables"), self);
    DATA_PTR(self) = sprite;
    DATA_TYPE(self) = &sprite_data_type;
    return self;
}

void create_sprite_type(mrb_state* mrb) {
    struct RClass* type =  mrgss_class_new(mrb, "Sprite");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_OPT(1));
}