#include <mruby.h>
#include <mruby/data.h>
#include <mrgss.h>
#include <mrgss/utils.h>
#include <mrgss/structs.h>

static const struct mrb_data_type point_data_type = {
  "MRGSS::Point", mrb_free
};

static void build_point_from_point(MR_Point* src, MR_Point* dst) {
    dst->x = src->x;
    dst->y = src->y;
}

static void build_point_from_ints(MR_Point* dst, mrb_int x, mrb_int y) {
    dst->x = x;
    dst->y = y;
}

static mrb_value mrgss_point_initialize(mrb_state* mrb, mrb_value self) {
    MR_Point* cPoint;
    mrb_value x;
    mrb_int args, y;
    args = mrb_get_args(mrb, "|oi", &x, &y);
    cPoint = mrb_malloc(mrb, sizeof(MR_Point));
    switch (args) {
    case 0:
        build_point_from_ints(cPoint, 0,0);
        break;
    case 1:
        if (mrgss_obj_is_a(mrb, x, "Point")) {
            build_point_from_point(DATA_PTR(x), cPoint);
        } else {
            mrb_free(mrb, cPoint);
            mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_TYPE_ARGS);  
            return mrb_nil_value();  
        }
        break;
    case 2:
        if (is_number(mrb, x)) {
            build_point_from_ints(cPoint, mrb_int(mrb, x), y);
        } else {
            mrb_free(mrb, cPoint);
            mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_TYPE_ARGS);  
            return mrb_nil_value();
        }
        break;
    default:
        mrb_free(mrb, cPoint);
        mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_NUMBER_ARGS);
        return mrb_nil_value();
        break;
    }
    DATA_PTR(self) = cPoint;
    DATA_TYPE(self) = &point_data_type;
    return self;
}

static mrb_value mrgss_point_x_get(mrb_state* mrb, mrb_value self) {
    MR_Point* point = DATA_PTR(self);
    return mrb_fixnum_value(point->x);
}

static mrb_value mrgss_point_x_set(mrb_state* mrb, mrb_value self) {
    mrb_int new_value;
    MR_Point* point = DATA_PTR(self);
    mrb_get_args(mrb, "i", &new_value);
    point->x = new_value;
    return mrb_nil_value();
}

static mrb_value mrgss_point_y_get(mrb_state* mrb, mrb_value self) {
    MR_Point* point = DATA_PTR(self);
    return mrb_fixnum_value(point->y);
}

static mrb_value mrgss_point_y_set(mrb_state* mrb, mrb_value self) {
    mrb_int new_value;
    MR_Point* point = DATA_PTR(self);
    mrb_get_args(mrb, "i", &new_value);
    point->y = new_value;
    return mrb_nil_value();
}

void mrgss_point_init(mrb_state* mrb) {
    struct RClass* point = mrgss_class_new(mrb, "Point");
    mrb_define_method(mrb, point, "initialize", mrgss_point_initialize, MRB_ARGS_OPT(4));
    mrb_define_method(mrb, point, "x", mrgss_point_x_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, point, "x=", mrgss_point_x_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, point, "y", mrgss_point_y_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, point, "y=", mrgss_point_y_set, MRB_ARGS_REQ(1));
}