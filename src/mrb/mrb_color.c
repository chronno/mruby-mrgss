#include <mruby.h>
#include <mruby/data.h>
#include <mrgss.h>
#include <mrgss/color.h>

static const struct mrb_data_type color_data_type = {
  "MRGSS::Color", mrb_free
};

static mrb_value initialize(mrb_state *mrb, mrb_value self) {
    Color *color;
    mrb_int r, g, b, a;
    mrb_get_args(mrb, "iiii", &r, &g, &b, &a);
    color = mrb_malloc(mrb, sizeof(Color));
    *color = (Color){.r = r, .g = g, .b = b, .a = a};
    DATA_PTR(self) = color;
    DATA_TYPE(self) = &color_data_type;
    return self;
}

static mrb_value set_r(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Color* color = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    color->r = value;
    return self;
}

static mrb_value set_g(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Color* color = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    color->g = value;
    return self;
}

static mrb_value set_b(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Color* color = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    color->b = value;
    return self;
}

static mrb_value set_a(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Color* color = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    color->a = value;
    return self;
}

static mrb_value get_r(mrb_state* mrb, mrb_value self) {
    Color* color = DATA_PTR(self);
    return mrb_fixnum_value(color->r);
}

static mrb_value get_g(mrb_state* mrb, mrb_value self) {
    Color* color = DATA_PTR(self);
    return mrb_fixnum_value(color->g);
}

static mrb_value get_b(mrb_state* mrb, mrb_value self) {
    Color* color = DATA_PTR(self);
    return mrb_fixnum_value(color->b);
}

static mrb_value get_a(mrb_state* mrb, mrb_value self) {
    Color* color = DATA_PTR(self);
    return mrb_fixnum_value(color->a);
}

static mrb_value set(mrb_state* mrb, mrb_value self) {
    mrb_value arg;
    mrb_int args, g, b, a;
    Color *color, *other;
    args = mrb_get_args(mrb, "o|iii", &arg, &g, &b, &a);
    color = DATA_PTR(self);
    switch (args) {
    case 1:
        if (is_a(mrb, arg, "Color")) {
            other = DATA_PTR(arg);
            color->r = other->r;
            color->g = other->g;
            color->b = other->b;
            color->a = other->a;
        } else {
            mrb_raise(mrb, E_ARGUMENT_ERROR, "Color expected");
        }
        break;
    case 4:
        if (is_fixnum(mrb, arg)) {
            color->r = mrb_int(mrb, arg);
            color->g = g;
            color->b = b;
            color->a = a;
        } else {
            mrb_raise(mrb, E_ARGUMENT_ERROR, "Number expected");
        }
        break;
    default:
        mrb_raise(mrb, E_ARGUMENT_ERROR, "Number expected");
        break;
    }
    return self;
}


void create_color_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Color");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_OPT(4));
    mrb_define_method(mrb, type, "red=", set_r, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "green=", set_g, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "blue=", set_b, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "alpha=", set_a, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "red", get_r, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "green", get_g, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "blue", get_b, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "alpha", get_a, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "set", set, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(3));
}