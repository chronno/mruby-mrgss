#include <mruby.h>
#include <mruby/data.h>
#include <mruby/array.h>
#include <mrgss.h>
#include <mrgss/viewport.h>

static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    mrb_int argc, y,w,h;
    mrb_value arg1;
    mrb_value rectars[4];
    argc = mrb_get_args(mrb, "o|iii", &arg1, &y, &w, &h);
    switch (argc) {
    case 1:
        if (is_a(mrb, arg1, "Rect")) {
            SET_IV("@rect", arg1);
        } else {
            mrb_raise(mrb, E_ARGUMENT_ERROR, "rect required");
        }
        break;
    case 4:
        if(is_fixnum(mrb, arg1)) {
            rectars[0] = arg1;
            rectars[1] = mrb_fixnum_value(y);
            rectars[2] = mrb_fixnum_value(w);
            rectars[3] = mrb_fixnum_value(h);
            SET_IV("@rect", mrgss_instance_new(mrb, "Rect", 4, rectars));

        } else {
            mrb_raise(mrb, E_ARGUMENT_ERROR, "fixnum required");
        }
        break;
    default:
        mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong number of arguments");
        break;
    }
    SET_IV("#drawables", mrb_ary_new(mrb));
    SET_IV("@visible", mrb_true_value());
    return self;
}

void create_viewport_type(mrb_state* mrb) {
    struct RClass* type =  mrgss_class_new(mrb, "Viewport");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(4));
}