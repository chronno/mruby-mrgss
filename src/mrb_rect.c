#include <mruby.h>
#include <mruby/data.h>
#include <mrgss.h>
#include <mrgss/utils.h>
#include <mrgss/structs.h>

static const struct mrb_data_type rect_data_type = {
  "MRGSS::Rect", mrb_free
};

static void build_rect_from_rect(MR_Rect* src, MR_Rect* dst) {
    dst->x = src->x;
    dst->y = src->y;
    dst->w = src->w;
    dst->h = src->h;
}

static void build_rect_from_ints(MR_Rect* dst, mrb_int x, mrb_int y, mrb_int w, mrb_int h) {
    dst->x = x;
    dst->y = y;
    dst->w = w;
    dst->h = h;
}

static void build_rect_from_points(MR_Rect* dst, MR_Point* position, MR_Point* size) {
    dst->x = position->x;
    dst->y = position->y;
    dst->w = size->x;
    dst->h = size->y;
}

static void build_rect_from_point(MR_Rect* dst, MR_Point* position, mrb_int width, mrb_int height) {
    dst->x = position->x;
    dst->y = position->y;
    dst->w = width;
    dst->h = height;
}


static mrb_value mrgss_rect_initialize(mrb_state* mrb, mrb_value self) {
    MR_Rect* cRect;
    mrb_value x, y;
    mrb_int args, w, h;
    args = mrb_get_args(mrb, "|ooii", &x, &y, &w, &h);
    cRect = mrb_malloc(mrb, sizeof(MR_Rect));
    switch (args) {
    case 0:
        build_rect_from_ints(cRect, 0,0,0,0);
        break;
    case 1:
        if (mrgss_obj_is_a(mrb, x, "Rect")) {
            build_rect_from_rect(DATA_PTR(x), cRect);
        } else {
            mrb_free(mrb, cRect);
            mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_TYPE_ARGS);  
            return mrb_nil_value();  
        }
        break;
    case 2:
        if (mrgss_obj_is_a(mrb, x, "Point") && mrgss_obj_is_a(mrb, y, "Point")) {
            build_rect_from_points(cRect, DATA_PTR(x), DATA_PTR(y));
        } else if (mrgss_obj_is_a(mrb, x, "Point") && is_number(mrb, y)) {
            build_rect_from_point(cRect, DATA_PTR(x), mrb_int(mrb,y), mrb_int(mrb,y));
        } else if (is_number(mrb, x) && is_number(mrb, y)) {
            build_rect_from_ints(cRect, 0,0, mrb_int(mrb,x), mrb_int(mrb,y));
        } else {
            mrb_free(mrb, cRect);
            mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_TYPE_ARGS);  
            return mrb_nil_value();
        }
        break;
    case 3:
        if (mrgss_obj_is_a(mrb, x, "Point") && is_number(mrb, y)) {
            build_rect_from_point(cRect, DATA_PTR(x), mrb_int(mrb,y), w);
        } else {
            mrb_free(mrb, cRect);
            mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_TYPE_ARGS);  
            return mrb_nil_value();
        }
    case 4:
        if (is_number(mrb, x) && is_number(mrb, y)) {
            build_rect_from_ints(cRect, mrb_int(mrb,x), mrb_int(mrb,y), w, h);
        } else {
            mrb_free(mrb, cRect);
            mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_TYPE_ARGS);  
            return mrb_nil_value();
        }
        break;
    default:
        mrb_free(mrb, cRect);
        mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_NUMBER_ARGS);
        return mrb_nil_value();
        break;
    }
    DATA_PTR(self) = cRect;
    DATA_TYPE(self) = &rect_data_type;
    return self;
}

static mrb_value mrgss_rect_x_get(mrb_state* mrb, mrb_value self) {
    MR_Rect* rect = DATA_PTR(self);
    return mrb_fixnum_value(rect->x);
}

static mrb_value mrgss_rect_x_set(mrb_state* mrb, mrb_value self) {
    mrb_int new_value;
    MR_Rect* rect = DATA_PTR(self);
    mrb_get_args(mrb, "i", &new_value);
    rect->x = new_value;
    return mrb_nil_value();
}

static mrb_value mrgss_rect_y_get(mrb_state* mrb, mrb_value self) {
    MR_Rect* rect = DATA_PTR(self);
    return mrb_fixnum_value(rect->y);
}

static mrb_value mrgss_rect_y_set(mrb_state* mrb, mrb_value self) {
    mrb_int new_value;
    MR_Rect* rect = DATA_PTR(self);
    mrb_get_args(mrb, "i", &new_value);
    rect->y = new_value;
    return mrb_nil_value();
}

static mrb_value mrgss_rect_w_get(mrb_state* mrb, mrb_value self) {
    MR_Rect* rect = DATA_PTR(self);
    return mrb_fixnum_value(rect->w);
}

static mrb_value mrgss_rect_w_set(mrb_state* mrb, mrb_value self) {
    mrb_int new_value;
    MR_Rect* rect = DATA_PTR(self);
    mrb_get_args(mrb, "i", &new_value);
    rect->w = new_value;
    return mrb_nil_value();
}

static mrb_value mrgss_rect_h_get(mrb_state* mrb, mrb_value self) {
    MR_Rect* rect = DATA_PTR(self);
    return mrb_fixnum_value(rect->h);
}

static mrb_value mrgss_rect_h_set(mrb_state* mrb, mrb_value self) {
    mrb_int new_value;
    MR_Rect* rect = DATA_PTR(self);
    mrb_get_args(mrb, "i", &new_value);
    rect->h = new_value;
    return mrb_nil_value();
}

void mrgss_rectangle_init(mrb_state* mrb) {
    struct RClass* rect = mrgss_class_new(mrb, "Rect");
    mrb_define_method(mrb, rect, "initialize", mrgss_rect_initialize, MRB_ARGS_OPT(4));
    mrb_define_method(mrb, rect, "x", mrgss_rect_x_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, rect, "x=", mrgss_rect_x_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rect, "y", mrgss_rect_y_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, rect, "y=", mrgss_rect_y_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rect, "width", mrgss_rect_w_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, rect, "width=", mrgss_rect_w_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rect, "height", mrgss_rect_h_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, rect, "height=", mrgss_rect_h_set, MRB_ARGS_REQ(1));
}