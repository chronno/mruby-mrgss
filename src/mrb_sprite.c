#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>
#include <raylib.h>

#include <mrgss.h>
#include <mrgss/utils.h>
#include <mrgss/structs.h>



static void mrgss_sprite_free(mrb_state *mrb, void *p) {
    if (p) {       
        mrb_free(mrb, p);
    }
}

static const struct mrb_data_type sprite_data_type = {
  "MRGSS::Sprite", mrgss_sprite_free
};

static mrb_value mrgss_sprite_initialize(mrb_state* mrb, mrb_value self) {
    mrb_int args;
    mrb_value bitmap;
    mrb_value rect;
    MR_Sprite *sprite = mrb_malloc(mrb, sizeof(MR_Sprite));
    args = mrb_get_args(mrb, "o|o", &bitmap, &rect);
    switch (args) {
    case 1:
        sprite->bitmap = DATA_PTR(bitmap);
        sprite->texture = LoadTextureFromImage(sprite->bitmap->image);
        sprite->srcRect = (MR_Rect){0, 0,  sprite->texture.width, sprite->texture.height};
        sprite->dstRect = (MR_Rect){0, 0,  sprite->bitmap->image.width, sprite->bitmap->image.height};
        sprite->angle = 0;
        DATA_PTR(self) = sprite;
        DATA_TYPE(self) = &sprite_data_type;
        break;
    default:
        mrb_free(mrb, sprite);
        mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_NUMBER_ARGS);
        break;
    }
    return self;
}


static mrb_value mrgss_sprite_draw(mrb_state* mrb, mrb_value self) {
    Rectangle src, dst;
    MR_Sprite* sprite = DATA_PTR(self);
    src = (Rectangle){sprite->srcRect.x, sprite->srcRect.y, sprite->srcRect.w, sprite->srcRect.h};
    dst = (Rectangle){sprite->dstRect.x, sprite->dstRect.y, sprite->dstRect.w, sprite->dstRect.h};
    DrawTexturePro(sprite->texture, src, dst, (Vector2){0,0} , sprite->angle, (Color){255,255,255,255});  
    return mrb_nil_value();
}

static mrb_value mrgss_sprite_x_get(mrb_state* mrb, mrb_value self) {
    MR_Sprite* sprite = DATA_PTR(self);
    return mrb_fixnum_value(sprite->dstRect.x);
}

static mrb_value mrgss_sprite_x_set(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    MR_Sprite* sprite = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    sprite->dstRect.x = value;
    return mrb_nil_value();
}


static mrb_value mrgss_sprite_y_get(mrb_state* mrb, mrb_value self) {
    MR_Sprite* sprite = DATA_PTR(self);
    return mrb_fixnum_value(sprite->dstRect.y);
}

static mrb_value mrgss_sprite_y_set(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    MR_Sprite* sprite = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    sprite->dstRect.y = value;
    return mrb_nil_value();
}


void mrgss_sprite_init(mrb_state *mrb) {
    struct RClass* sprite = mrgss_class_new(mrb, "Sprite");
    mrb_define_method(mrb, sprite, "initialize", mrgss_sprite_initialize, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(2));
    mrb_define_method(mrb, sprite, "x", mrgss_sprite_x_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "x=", mrgss_sprite_x_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sprite, "y", mrgss_sprite_y_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "y=", mrgss_sprite_y_set, MRB_ARGS_REQ(1));

    mrb_define_method(mrb, sprite, "draw", mrgss_sprite_draw, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
}