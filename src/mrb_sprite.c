#include <mruby.h>
#include <mruby/data.h>
#include <mruby/array.h>
#include <mruby/variable.h>
#include <mruby/object.h>
#include <mrb_mrgss.h>
#include <mrgss.h>
#include <mrgss/utils.h>
#include <mrgss/structs.h>

struct mrb_data_type const sprite_data_type = {"MRGSS::Sprite", mrb_free};

static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    mrb_value game;
    Sprite* sprite;
    MRG_SET_PROP("@bitmap", mrb_nil_value());
    MRG_SET_PROP("@x", mrb_fixnum_value(0));
    MRG_SET_PROP("@y", mrb_fixnum_value(0));
    MRG_SET_PROP("@ox", mrb_fixnum_value(0));
    MRG_SET_PROP("@oy", mrb_fixnum_value(0));
    MRG_SET_PROP("@zoom_x", mrb_float_value(mrb, 1));
    MRG_SET_PROP("@zoom_y", mrb_float_value(mrb, 1));
    MRG_SET_PROP("@src_rect", mrb_nil_value());
    MRG_SET_PROP("@visible", mrb_true_value());
    MRG_SET_PROP("@angle", mrb_fixnum_value(0));
    MRG_SET_PROP("@opacity", mrb_fixnum_value(255));
    sprite = mrb_malloc(mrb, sizeof(Sprite));
    sprite->x = 0;
    sprite->y = 0;
    sprite->rx = 0;
    sprite->ry = 0;
    sprite->rw = 0;
    sprite->rh = 0;
    DATA_PTR(self) = sprite;
    DATA_TYPE(self) = &sprite_data_type;
    game = mrb_gv_get(mrb, mrb_intern_lit(mrb, "$MRGSS"));
    mrb_ary_push(mrb, MRG_GET_PROP_FROM(game, "drawables"), self);
    return self;
}


mrb_value set_bitmap(mrb_state* mrb, mrb_value self) {
    Sprite* sprite;
    mrb_value value;
    mrb_value args[4];
    mrb_get_args(mrb, "o", &value);
    if (mrgss_obj_is_a(mrb, value, "Bitmap")) {
        args[0] = mrb_fixnum_value(0);
        args[1] = mrb_fixnum_value(0);
        args[2] = MRG_GET_PROP_FROM(value, "@width");
        args[3] = MRG_GET_PROP_FROM(value, "@height");
        MRG_SET_PROP("@bitmap", value);
        MRG_SET_PROP("@src_rect", mrgss_instance_new(mrb, "Rect", 4, args));
        sprite = DATA_PTR(self);
        sprite->rw = mrb_int(mrb, args[2]);
        sprite->rh = mrb_int(mrb, args[3]);
        sync_sprite(mrb, self);
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "wanted a bitmap");
    }
    return mrb_nil_value();
}

mrb_value get_bitmap(mrb_state* mrb, mrb_value self) {
    return MRG_GET_PROP("@bitmap");
}


mrb_value set_rect(mrb_state* mrb, mrb_value self) {
    mrb_value value;
    mrb_value args[4];
    mrb_get_args(mrb, "o", &value);
    if (mrgss_obj_is_a(mrb, value, "Rect")) {
        MRG_SET_PROP("@src_rect", value);
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "wanted a bitmap");
    }
    return mrb_nil_value();
}

mrb_value get_rect(mrb_state* mrb, mrb_value self) {
    return MRG_GET_PROP("@src_rect");
}

void create_sprite_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Sprite");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "bitmap=", set_bitmap, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "bitmap", get_bitmap, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "src_rect=", set_rect, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "src_rect", get_rect, MRB_ARGS_NONE());
}