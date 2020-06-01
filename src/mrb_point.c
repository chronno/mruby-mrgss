#include <mrgss.h>

static const struct mrb_data_type point_data_type = {
  "MRGSS::Point", mrb_free
};

static mrb_value initialize(mrb_state *mrb, mrb_value self) {
    Point *point;
    mrb_int args, x, y;
    args = mrb_get_args(mrb, "|ii", &x, &y);
    point = mrb_malloc(mrb, sizeof(Point));
    switch (args) {
    case 0:
        point->x = 0;
        point->y = 0;
        break;
    case 2:
        point->x = x;
        point->y = y;
        break;
    default:
        mrb_free(mrb, point);
        mrb_raise(mrb, E_ARGUMENT_ERROR, "WRONG_NUMBER_ARGS");
        return mrb_nil_value();
        break;
    }
    DATA_PTR(self) = point;
    DATA_TYPE(self) = &point_data_type;
    return self;
}

static mrb_value set_x(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Point* point = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    point->x = value;
    return self;
}

static mrb_value set_y(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Point* point = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    point->y = value;
    return self;
}

static mrb_value get_x(mrb_state* mrb, mrb_value self) {
    Point* point = DATA_PTR(self);
    return mrb_fixnum_value(point->x);
}

static mrb_value get_y(mrb_state* mrb, mrb_value self) {
    Point* point = DATA_PTR(self);
    return mrb_fixnum_value(point->y);
}



void create_point_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Point");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_OPT(2));
    mrb_define_method(mrb, type, "x=", set_x, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "y=", set_y, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "x", get_x, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "y", get_y, MRB_ARGS_REQ(1));
}