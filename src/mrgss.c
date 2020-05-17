#include <string.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <mrgss.h>

#define MRGSS_MODULE mrb_module_get(mrb, "MRGSS")


mrb_int cap_to_byte(mrb_int value) {
    return value > 255 ? 255 : value < 0 ? 0 : value;
}

struct RClass* mrgss_module_init(mrb_state *mrb) {
    return mrb_define_module(mrb, "MRGSS");
}

struct RClass* mrgss_create_class(mrb_state *mrb, const char *name) {
    return mrb_define_class_under(mrb, MRGSS_MODULE, name, mrb->object_class);
}

void mrgss_iv_create(mrb_state *mrb, mrb_value object, const char* name, mrb_value value){
    mrb_sym symbol = mrb_intern_static(mrb, name, strlen(name));
    mrb_iv_set(mrb, object, symbol, value);
}