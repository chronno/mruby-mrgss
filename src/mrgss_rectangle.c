#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <raylib.h>
#include <mrgss.h>

#define MRGSS_MODULE mrb_module_get(mrb, "MRGSS")

static const struct mrb_data_type rectangle_data_type = {
  "MRGSS::Rectangle", mrb_free
};

static mrb_value mrgss_rectangle_initialize(mrb_state *mrb, mrb_value self) {
    Rectangle* rect;
    mrb_value x, y, width, height;
    mrb_int args;
    args = mrb_get_args(mrb, "|oooo", &x, &y, &width, &height);
    rect = mrb_malloc(mrb, sizeof(Rectangle));
    switch (args) {
    case 0:
      rect->x = 0.0;
      rect->y = 0.0;
      
      break;
    case 2:
      rect->x = mrb_int(mrb, x);
      rect->y = mrb_int(mrb, y);
      rect->width = 0.0;
      rect->height = 0.0; 
      break;
    case 4:
      rect->x = mrb_int(mrb, x);
      rect->y = mrb_int(mrb, y);
      rect->width =mrb_int(mrb, width);
      rect->height = mrb_int(mrb, height); 
      break;
    default:
      mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_NUMBER_ARGS);
      break;
    }  
    DATA_PTR(self) = rect;
    DATA_TYPE(self) = &rectangle_data_type;
    return self;
}

static mrb_value mrgss_rectangle_x_get(mrb_state *mrb, mrb_value self) {
  Rectangle *value = DATA_PTR(self);
  return mrb_fixnum_value(value->x);
}

static mrb_value mrgss_rectangle_x_set(mrb_state *mrb, mrb_value self) {
  mrb_value new_value;
  Rectangle *value = DATA_PTR(self);
  mrb_get_args(mrb, "o", &new_value);
  value->x = mrb_int(mrb, new_value);
  return mrb_nil_value();
}

static mrb_value mrgss_rectangle_y_get(mrb_state *mrb, mrb_value self) {
  Rectangle *value = DATA_PTR(self);
  return mrb_fixnum_value(value->y);
}

static mrb_value mrgss_rectangle_y_set(mrb_state *mrb, mrb_value self) {
  mrb_value new_value;
  Rectangle *value = DATA_PTR(self);
  mrb_get_args(mrb, "o", &new_value);
  value->y = mrb_int(mrb, new_value);
  return mrb_nil_value();
}

static mrb_value mrgss_rectangle_width_get(mrb_state *mrb, mrb_value self) {
  Rectangle *value = DATA_PTR(self);
  return mrb_fixnum_value(value->width);
}

static mrb_value mrgss_rectangle_width_set(mrb_state *mrb, mrb_value self) {
  mrb_value new_value;
  Rectangle *value = DATA_PTR(self);
  mrb_get_args(mrb, "o", &new_value);
  value->width = mrb_int(mrb, new_value);
  return mrb_nil_value();
}

static mrb_value mrgss_rectangle_height_get(mrb_state *mrb, mrb_value self) {
  Rectangle *value = DATA_PTR(self);
  return mrb_fixnum_value(value->height);
}

static mrb_value mrgss_rectangle_height_set(mrb_state *mrb, mrb_value self) {
  mrb_value new_value;
  Rectangle *value = DATA_PTR(self);
  mrb_get_args(mrb, "o", &new_value);
  value->height = mrb_int(mrb, new_value);
  return mrb_nil_value();
}

static mrb_value mrgss_rectangle_empty(mrb_state *mrb, mrb_value self) {
  Rectangle* value = DATA_PTR(self);
  value->x = 0.0;
  value->y = 0.0;
  value->width = 0.0;
  value->height = 0.0;
  return mrb_nil_value();
}

static mrb_value mrgss_rectangle_set(mrb_state *mrb, mrb_value self) {
  mrb_int args;
  mrb_value other;
  mrb_int y, width, height;
  Rectangle* other_value;
  Rectangle* value = DATA_PTR(self);  
  args = mrb_get_args(mrb, "o|fff", &other, &y, &width, &height);
  switch (args) {
  case 1:
    other_value = DATA_PTR(other);
    value->x = other_value->x;
    value->y = other_value->y;
    value->width = other_value->width;
    value->height = other_value->height;
    break;
  case 4:
    value->x = mrb_int(mrb, other);
    value->y = y * 1.0;
    value->width = width * 1.0;
    value->height = height * 1.0;
    break;
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_NUMBER_ARGS);
    break;
  }
  return mrb_nil_value();
}

void mrgss_rectangle_init(mrb_state *mrb) {
    struct RClass* mrb_rectangle = mrgss_create_class(mrb, "Rectangle");
    mrb_define_method(mrb, mrb_rectangle, "initialize", mrgss_rectangle_initialize, MRB_ARGS_OPT(4));
    mrb_define_method(mrb, mrb_rectangle, "x", mrgss_rectangle_x_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_rectangle, "x=", mrgss_rectangle_x_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_rectangle, "y", mrgss_rectangle_y_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_rectangle, "y=", mrgss_rectangle_y_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_rectangle, "width", mrgss_rectangle_width_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_rectangle, "width=", mrgss_rectangle_width_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_rectangle, "height", mrgss_rectangle_height_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_rectangle, "height=", mrgss_rectangle_height_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_rectangle, "empty", mrgss_rectangle_empty, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_rectangle, "set", mrgss_rectangle_set, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(3));
}

mrb_value create_rectangle_from(mrb_state* mrb, mrb_int x, mrb_int y, mrb_int width, mrb_int height) {
  mrb_value params[4] = {mrb_fixnum_value(x),mrb_fixnum_value(y), mrb_fixnum_value(width), mrb_fixnum_value(height)};
  return mrb_obj_new(mrb, mrb_class_get_under(mrb, MRGSS_MODULE, "Rectangle"), 4, params);
}