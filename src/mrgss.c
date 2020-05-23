#include <stdlib.h>
#include <string.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <mrgss.h>

struct RClass* mrgss_module(mrb_state *mrb) {
    return mrb_module_get(mrb, "MRGSS");
}

mrb_int cap_to_byte(mrb_int value) {
    return value > 255 ? 255 : value < 0 ? 0 : value;
}

struct RClass* mrgss_module_init(mrb_state *mrb) {
    return mrb_define_module(mrb, "MRGSS");
}

struct RClass* mrgss_create_class(mrb_state *mrb, const char *name) {
    return mrb_define_class_under(mrb, mrgss_module(mrb), name, mrb->object_class);
}

void mrgss_iv_create(mrb_state *mrb, mrb_value object, const char* name, mrb_value value){
    mrb_sym symbol = mrb_intern_static(mrb, name, strlen(name));
    mrb_iv_set(mrb, object, symbol, value);
}

mrb_value mrgss_iv_get(mrb_state *mrb, mrb_value object, const char* name){
    mrb_sym symbol = mrb_intern_static(mrb, name, strlen(name));
    return mrb_iv_get(mrb, object, symbol);
}

struct RClass* mrgss_get_class(mrb_state *mrb, const char* name){
    return mrb_class_get_under(mrb, mrgss_module(mrb), name);
}

mrb_bool mrgss_obj_is_a(mrb_state *mrb, mrb_value obj, const char* name) {
    return mrb_obj_is_kind_of(mrb, obj, mrgss_get_class(mrb, name));
}

mrb_bool is_number(mrb_state *mrb, mrb_value obj) {
    return mrb_obj_is_kind_of(mrb, obj, mrb_class_get(mrb, "Fixnum"));
}

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
const char* get_endpoint(const char* file) {
    char* host = emscripten_run_script_string("/.*(?=\\/\\w*)/.exec(window.location.href).join() + '/'");
	char* endpoint = malloc(strlen(host) + strlen(file) + 1);
	strcpy(endpoint, host);
	strcat(endpoint, file);
	return endpoint;
}
#endif