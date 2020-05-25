#include <mruby.h>
#include <mruby/data.h>
#include <mrgss.h>
#include <mrgss/utils.h>
#include <mrgss/structs.h>

static const struct mrb_data_type color_data_type = {
  "MRGSS::Color", mrb_free
};


static mrb_value mrgss_color_initialize(mrb_state* mrb, mrb_value self) {
    MR_Color* cColor;
    mrb_int r, g, b, a;
    mrb_get_args(mrb, "iiii", &r, &g, &b, &a);
    cColor = mrb_malloc(mrb, sizeof(MR_Color));
    cColor->r = r;
    cColor->g = g;
    cColor->b = b;
    cColor->a = a;
    DATA_PTR(self) = cColor;
    DATA_TYPE(self) = &color_data_type;
    return self;
}

static mrb_value mrgss_color_r_get(mrb_state* mrb, mrb_value self) {
    MR_Color* color = DATA_PTR(self);
    return mrb_fixnum_value(color->r);
}

static mrb_value mrgss_color_r_set(mrb_state* mrb, mrb_value self) {
    mrb_int new_value;
    MR_Color* color = DATA_PTR(self);
    mrb_get_args(mrb, "i", &new_value);
    color->r = new_value;
    return mrb_nil_value();
}

static mrb_value mrgss_color_g_get(mrb_state* mrb, mrb_value self) {
    MR_Color* color = DATA_PTR(self);
    return mrb_fixnum_value(color->g);
}

static mrb_value mrgss_color_g_set(mrb_state* mrb, mrb_value self) {
    mrb_int new_value;
    MR_Color* color = DATA_PTR(self);
    mrb_get_args(mrb, "i", &new_value);
    color->g = new_value;
    return mrb_nil_value();
}

static mrb_value mrgss_color_b_get(mrb_state* mrb, mrb_value self) {
    MR_Color* color = DATA_PTR(self);
    return mrb_fixnum_value(color->b);
}

static mrb_value mrgss_color_b_set(mrb_state* mrb, mrb_value self) {
    mrb_int new_value;
    MR_Color* color = DATA_PTR(self);
    mrb_get_args(mrb, "i", &new_value);
    color->b = new_value;
    return mrb_nil_value();
}

static mrb_value mrgss_color_a_get(mrb_state* mrb, mrb_value self) {
    MR_Color* color = DATA_PTR(self);
    return mrb_fixnum_value(color->r);
}

static mrb_value mrgss_color_a_set(mrb_state* mrb, mrb_value self) {
    mrb_int new_value;
    MR_Color* color = DATA_PTR(self);
    mrb_get_args(mrb, "i", &new_value);
    color->r = new_value;
    return mrb_nil_value();
}

void mrgss_color_init(mrb_state* mrb) {
    struct RClass* color = mrgss_class_new(mrb, "Color");
    mrb_define_method(mrb, color, "initialize", mrgss_color_initialize, MRB_ARGS_OPT(4));
    mrb_define_method(mrb, color, "r", mrgss_color_r_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, color, "r=", mrgss_color_r_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, color, "g", mrgss_color_g_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, color, "g=", mrgss_color_g_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, color, "b", mrgss_color_b_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, color, "b=", mrgss_color_b_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, color, "a", mrgss_color_a_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, color, "a=", mrgss_color_a_set, MRB_ARGS_REQ(1));
}