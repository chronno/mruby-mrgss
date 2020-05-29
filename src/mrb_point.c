#include <mruby.h>
#include <mrb_mrgss.h>
#include <mrgss/utils.h>


static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    mrb_int x, y;
    mrb_get_args(mrb, "ii", &x, &y);
    MRG_SET_PROP("@x", mrb_fixnum_value(x));
    MRG_SET_PROP("@y", mrb_fixnum_value(y));
    return self;
}
void create_point_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Point");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(2));
}