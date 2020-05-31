#include <mrgss.h>

struct mrb_data_type const sprite_data_type = {"MRGSS::Sprite", mrb_free};

static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    Sprite* sprite = mrb_malloc(mrb, sizeof(Sprite));
    sprite->x = 0;
    sprite->y = 0;
    sprite->rx = 0;
    sprite->ry = 0;
    sprite->rw = 0;
    sprite->rh = 0;
    DATA_PTR(self) = sprite;
    DATA_TYPE(self) = &sprite_data_type;
    return self;
}


mrb_value set_bitmap(mrb_state* mrb, mrb_value self) {
    Sprite* sprite;
    mrb_value value;
    mrb_get_args(mrb, "o", &value);
    if (mrgss_obj_is_a(mrb, value, "Bitmap")) {
        Bitmap* bmp = DATA_PTR(value);
        sprite = DATA_PTR(self);
        sprite->rw =  bmp->width;
        sprite->rh =  bmp->height;
        sprite->dirty = TRUE;
        MRG_SET_PROP("#bitmap", value);
        sync_sprite(mrb, self);        
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "wanted a Bitmap");
    }
    return mrb_nil_value();
}

mrb_value get_bitmap(mrb_state* mrb, mrb_value self) {
    return MRG_GET_PROP("#bitmap");
}


mrb_value set_rect(mrb_state* mrb, mrb_value self) {
    mrb_value value;
    Sprite* sprite;
    Rect* rect;
    mrb_get_args(mrb, "o", &value);
    if (mrgss_obj_is_a(mrb, value, "Rect")) {
        MRG_SET_PROP("#src_rect", value);
        sprite = DATA_PTR(self);
        rect = DATA_PTR(value);
        sprite->rx = rect->x;
        sprite->ry = rect->y;
        sprite->rw = rect->w;
        sprite->rh = rect->h;
        sync_sprite(mrb, self);
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "wanted a Rect");
    }
    return mrb_nil_value();
}

mrb_value get_rect(mrb_state* mrb, mrb_value self) {
    return MRG_GET_PROP("#src_rect");
}

mrb_value set_x(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Sprite* sprite = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    sprite->x = value;
    sync_sprite(mrb, self);
    return self;
}

mrb_value get_x(mrb_state* mrb, mrb_value self) {
    Sprite* sprite = DATA_PTR(self);
    return mrb_fixnum_value(sprite->x);
}

mrb_value set_y(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Sprite* sprite = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    sprite->y = value;
    sync_sprite(mrb, self);
    return self;
}

mrb_value get_y(mrb_state* mrb, mrb_value self) {
    Sprite* sprite = DATA_PTR(self);
    return mrb_fixnum_value(sprite->y);
}

void create_sprite_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Sprite");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "bitmap=", set_bitmap, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "bitmap", get_bitmap, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "src_rect=", set_rect, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "src_rect", get_rect, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "x=", set_x, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "x", get_x, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "y=", set_x, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "y", get_x, MRB_ARGS_NONE());
}