#include <mruby.h>
#include <mrb_mrgss.h>
#include <mrgss/utils.h>


static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    mrb_int r, g, b, a;
    mrb_get_args(mrb, "iiii", &r, &g, &b, &a);
    MRG_SET_PROP("@red", mrb_fixnum_value(r));
    MRG_SET_PROP("@green", mrb_fixnum_value(g));
    MRG_SET_PROP("@blue", mrb_fixnum_value(b));
    MRG_SET_PROP("@alpha", mrb_fixnum_value(a));
    return self;
}

void create_color_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Color");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(4));
}