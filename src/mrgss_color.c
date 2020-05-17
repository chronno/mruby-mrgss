#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <raylib.h>
#include <mrgss.h>

#define MRGSS_MODULE mrb_module_get(mrb, "MRGSS")

static const struct mrb_data_type color_data_type = {
  "MRGSS::Color", mrb_free
};

static mrb_value mrgss_color_initialize(mrb_state *mrb, mrb_value self) {
    Color* color;
    mrb_value r, g, b, a;
    mrb_int args;
    args = mrb_get_args(mrb, "|oooo", &r, &g, &b, &a);
    color = mrb_malloc(mrb, sizeof(Color*));
    switch (args) {
    case 0:
      color->r = 0;
      color->g = 0;
      color->b = 0;
      color->a = 255;
      break;
    case 4:
      color->r = cap_to_byte(mrb_int(mrb, r));
      color->g = cap_to_byte(mrb_int(mrb, g));
      color->b = cap_to_byte(mrb_int(mrb, b));
      color->a = cap_to_byte(mrb_int(mrb, a)); 
      break;
    default:
      mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_NUMBER_ARGS);
      break;
    }  
    DATA_PTR(self) = color;
    DATA_TYPE(self) = &color_data_type;
    return self;
}

static mrb_value mrgss_color_r_get(mrb_state* mrb, mrb_value self) {
  Color* value = DATA_PTR(self);
  return mrb_fixnum_value(value->r);
}

static mrb_value mrgss_color_r_set(mrb_state *mrb, mrb_value self) {
  mrb_int new_value;
  Color *value = DATA_PTR(self);
  mrb_get_args(mrb, "i", &new_value);
  value->r = cap_to_byte(new_value);
  return mrb_nil_value();
}

static mrb_value mrgss_color_g_get(mrb_state *mrb, mrb_value self) {
  Color *value = DATA_PTR(self);
  return mrb_fixnum_value(value->g);
}

static mrb_value mrgss_color_g_set(mrb_state *mrb, mrb_value self) {
  mrb_int new_value;
  Color* value = DATA_PTR(self);
  mrb_get_args(mrb, "i", &new_value);
  value->g = cap_to_byte(new_value);
  return mrb_nil_value();
}

static mrb_value mrgss_color_b_get(mrb_state *mrb, mrb_value self) {
  Color *value = DATA_PTR(self);
  return mrb_fixnum_value(value->b);
}

static mrb_value mrgss_color_b_set(mrb_state *mrb, mrb_value self) {
  mrb_int new_value;
  Color* value = DATA_PTR(self);
  mrb_get_args(mrb, "i", &new_value);
  value->b = cap_to_byte(new_value);
  return mrb_nil_value();
}

static mrb_value mrgss_color_a_get(mrb_state *mrb, mrb_value self) {
  Color *value = DATA_PTR(self);
  return mrb_fixnum_value(value->a);
}

static mrb_value mrgss_color_a_set(mrb_state *mrb, mrb_value self) {
  mrb_int new_value;
  Color* value = DATA_PTR(self);
  mrb_get_args(mrb, "i", &new_value);
  value->a = cap_to_byte(new_value);
  return mrb_nil_value();
}

static mrb_value mrgss_color_empty(mrb_state *mrb, mrb_value self) {
  Color* value = DATA_PTR(self);
  value->r = 0;
  value->g = 0;
  value->b = 0;
  value->a = 255;
  return mrb_nil_value();
}

static mrb_value mrgss_color_set(mrb_state *mrb, mrb_value self) {
  mrb_int args;
  mrb_value other;
  mrb_int g, b, a;
  Color* other_value;
  Color* value = DATA_PTR(self);  
  args = mrb_get_args(mrb, "o|iii", &other, &g, &b, &a);
  switch (args) {
  case 1:
    other_value = DATA_PTR(other);
    value->r = other_value->r;
    value->g = other_value->g;
    value->b = other_value->b;
    value->a = other_value->a;
    break;
  case 4:
    value->r = cap_to_byte(mrb_int(mrb, other));
    value->g = cap_to_byte(g);
    value->b = cap_to_byte(b);
    value->a = cap_to_byte(a);
    break;
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_NUMBER_ARGS);
    break;
  }
  return mrb_nil_value();
}

void mrgss_color_init(mrb_state *mrb) {
    struct RClass* mrb_rectangle = mrgss_create_class(mrb, "Color");
    mrb_define_method(mrb, mrb_rectangle, "initialize", mrgss_color_initialize, MRB_ARGS_OPT(4));
    mrb_define_method(mrb, mrb_rectangle, "r", mrgss_color_r_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_rectangle, "r=", mrgss_color_r_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_rectangle, "g", mrgss_color_g_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_rectangle, "g=", mrgss_color_g_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_rectangle, "b", mrgss_color_b_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_rectangle, "b=", mrgss_color_b_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_rectangle, "a", mrgss_color_a_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_rectangle, "a=", mrgss_color_a_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_rectangle, "empty", mrgss_color_empty, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_rectangle, "set", mrgss_color_set, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(3));
}

mrb_value create_color_from(mrb_state* mrb, mrb_int x, mrb_int y, mrb_int width, mrb_int height) {
  mrb_value params[4] = {mrb_fixnum_value(x),mrb_fixnum_value(y), mrb_fixnum_value(width), mrb_fixnum_value(height)};
  return mrb_obj_new(mrb, mrb_class_get_under(mrb, MRGSS_MODULE, "Rectangle"), 4, params);
}