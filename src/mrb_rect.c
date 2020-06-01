#include <mrgss.h>

static const struct mrb_data_type rect_data_type = {
  "MRGSS::Rect", mrb_free
};

static mrb_value initialize(mrb_state *mrb, mrb_value self) {
    Rect *rect;
    mrb_int args, x, y, w, h;
    args = mrb_get_args(mrb, "|iiii", &x, &y, &w, &h);
    rect = mrb_malloc(mrb, sizeof(Rect));
    switch (args) {
    case 0:
        rect->x = 0;
        rect->y = 0;
        rect->w = 0;
        rect->h = 0;
        DATA_PTR(self) = rect;
        DATA_TYPE(self) = &rect_data_type;
        break;
    case 4:
        rect->x = x;
        rect->y = y;
        rect->w = w;
        rect->h = h;
        DATA_PTR(self) = rect;
        DATA_TYPE(self) = &rect_data_type;
        break;
    default:
        mrb_raise(mrb, E_ARGUMENT_ERROR, "WRONG_NUMBER_ARGS");
        break;
    }
    return self;
}

static mrb_value set_x(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Rect* rect = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    rect->x = value;
    return self;
}

static mrb_value set_y(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Rect* rect = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    rect->y = value;
    return self;
}

static mrb_value set_w(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Rect* rect = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    rect->w = value;
    return self;
}

static mrb_value set_h(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Rect* rect = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    rect->h = value;
    return self;
}

static mrb_value get_x(mrb_state* mrb, mrb_value self) {
    Rect* rect = DATA_PTR(self);
    return mrb_fixnum_value(rect->x);
}

static mrb_value get_y(mrb_state* mrb, mrb_value self) {
    Rect* rect = DATA_PTR(self);
    return mrb_fixnum_value(rect->y);
}

static mrb_value get_w(mrb_state* mrb, mrb_value self) {
    Rect* rect = DATA_PTR(self);
    return mrb_fixnum_value(rect->w);
}

static mrb_value get_h(mrb_state* mrb, mrb_value self) {
    Rect* rect = DATA_PTR(self);
    return mrb_fixnum_value(rect->h);
}

void create_rect_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Rect");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_OPT(4));
    mrb_define_method(mrb, type, "x=", set_x, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "y=", set_y, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "width=", set_w, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "height=", set_h, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "x", get_x, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "y", get_y, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "width", get_w, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "height", get_h, MRB_ARGS_REQ(1));
}
