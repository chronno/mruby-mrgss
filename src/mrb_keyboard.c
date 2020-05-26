#include <mruby.h>
#include <raylib.h>
#include <mrgss.h>
#include <mrgss/utils.h>

static mrb_value mrgss_keyboard_trigger(mrb_state* mrb, mrb_value self) {
    mrb_int key;
    mrb_get_args(mrb, "i", &key);
    return mrb_bool_value(IsKeyPressed(key));
}

static mrb_value mrgss_keyboard_press(mrb_state* mrb, mrb_value self) {
    mrb_int key;
    mrb_get_args(mrb, "i", &key);
    return mrb_bool_value(IsKeyDown(key));
}


static mrb_value mrgss_keyboard_release(mrb_state* mrb, mrb_value self) {
    mrb_int key;
    mrb_get_args(mrb, "i", &key);
    return mrb_bool_value(IsKeyReleased(key));
}

void mrgss_keyboard_init(mrb_state* mrb) {
    struct RClass* keyboard = mrgss_class_new(mrb, "Keyboard");
    mrb_define_class_method(mrb, keyboard, "trigger?", mrgss_keyboard_trigger, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, keyboard, "press?", mrgss_keyboard_press, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, keyboard, "released?", mrgss_keyboard_release, MRB_ARGS_REQ(1));
}