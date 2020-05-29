#include <mruby.h>
#include <mrb_mrgss.h>
#include <mrgss/utils.h>


static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    mrb_int x, y, w, h;
    mrb_get_args(mrb, "iiii", &x, &y, &w, &h);
    MRG_SET_PROP("@x", mrb_fixnum_value(x));
    MRG_SET_PROP("@y", mrb_fixnum_value(y));
    MRG_SET_PROP("@width", mrb_fixnum_value(w));
    MRG_SET_PROP("@height", mrb_fixnum_value(h));
    return self;
}




void create_rect_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Rect");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(4));
}