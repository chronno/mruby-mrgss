#include <stdlib.h>
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
    mrb_value rectargs[4];
    MR_Bitmap *cbitmap;
    MR_Sprite *sprite = mrb_malloc(mrb, sizeof(MR_Sprite));
    
    args = mrb_get_args(mrb, "o|o", &bitmap, &rect);
    switch (args) {
    case 1:
        cbitmap = DATA_PTR(bitmap);
        MRG_SET_PROP("@bitmap", bitmap);
        rectargs[0] = mrb_fixnum_value(0);
        rectargs[1] = mrb_fixnum_value(0);
        rectargs[2] = mrb_fixnum_value(cbitmap->image.width);
        rectargs[3] = mrb_fixnum_value(cbitmap->image.height);
        MRG_SET_PROP("@src_rect", mrgss_instance_new(mrb, "Rect", 4, rectargs));
        sprite->dstRect = (MR_Rect){0, 0,  cbitmap->image.width, cbitmap->image.height};
        sprite->angle = 0;
        sprite->zoom_x = 0;
        sprite->zoom_y = 0;
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

static mrb_value mrgss_sprite_angle_get(mrb_state* mrb, mrb_value self) {
    MR_Sprite* sprite = DATA_PTR(self);
    return mrb_float_value(mrb, sprite->angle);
}

static mrb_value mrgss_sprite_angle_set(mrb_state* mrb, mrb_value self) {
    mrb_float value;
    MR_Sprite* sprite = DATA_PTR(self);
    mrb_get_args(mrb, "f", &value);
    sprite->angle = value;
    return mrb_nil_value();
}

static mrb_value mrgss_sprite_rect_get(mrb_state* mrb, mrb_value self) {
    return MRG_GET_PROP("@src_rect");
}

static mrb_value mrgss_sprite_rect_set(mrb_state* mrb, mrb_value self) {
    mrb_value value;
    mrb_get_args(mrb, "o", &value);
    if (mrgss_obj_is_a(mrb, value, "Rect") ) {
        MRG_SET_PROP("@src_rect", value);
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_TYPE_ARGS);
    }
    return mrb_nil_value();
}

static mrb_value mrgss_sprite_draw(mrb_state* mrb, mrb_value self) {
    MR_Rect* sSrcRect;
    Rectangle src, dst;
    MR_Bitmap *bitmap;
    MR_Sprite* sprite = DATA_PTR(self);
    sSrcRect = DATA_PTR(MRG_GET_PROP("@src_rect"));
    bitmap = DATA_PTR(MRG_GET_PROP("@bitmap"));
    src = (Rectangle){sSrcRect->x, sSrcRect->y, sSrcRect->w, sSrcRect->h};
    dst = (Rectangle){sprite->dstRect.x, sprite->dstRect.y, sSrcRect->w, sSrcRect->h};
    
    DrawTexturePro(bitmap->tex, src, dst, (Vector2){0,0} , sprite->angle, (Color){255,255,255,255});  
    return mrb_nil_value();
}

void mrgss_sprite_init(mrb_state *mrb) {
    struct RClass* sprite = mrgss_class_new(mrb, "Sprite");
    mrb_define_method(mrb, sprite, "initialize", mrgss_sprite_initialize, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(2));
    mrb_define_method(mrb, sprite, "x", mrgss_sprite_x_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "x=", mrgss_sprite_x_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sprite, "y", mrgss_sprite_y_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "y=", mrgss_sprite_y_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sprite, "angle", mrgss_sprite_angle_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "angle=", mrgss_sprite_angle_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sprite, "src_rect", mrgss_sprite_rect_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "src_rect=", mrgss_sprite_rect_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sprite, "draw", mrgss_sprite_draw, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
}