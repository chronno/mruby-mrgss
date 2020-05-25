#include <stdlib.h>
#include <string.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <mrgss/utils.h>

void mrgss_iv_set(mrb_state *mrb, mrb_value object, const char* name, mrb_value value) {
    mrb_sym symbol = mrb_intern_static(mrb, name, strlen(name));
    mrb_iv_set(mrb, object, symbol, value);
}

mrb_value mrgss_iv_get(mrb_state *mrb, mrb_value object, const char* name) {
    mrb_sym symbol = mrb_intern_static(mrb, name, strlen(name));
    return mrb_iv_get(mrb, object, symbol);
}


struct RClass* mrgss_module(mrb_state *mrb) {
    return mrb_module_get(mrb, "MRGSS");
}

struct RClass* mrgss_class_new(mrb_state *mrb, const char *name) {
    return mrb_define_class_under(mrb, mrgss_module(mrb), name, mrb->object_class);
}
 
struct RClass* mrgss_class_get(mrb_state *mrb, const char* name) {
    return mrb_class_get_under(mrb, mrgss_module(mrb), name);
}

mrb_value mrgss_instance_new(mrb_state *mrb, const char *type, mrb_int args_count,const mrb_value *args) {    
    return mrb_obj_new(mrb, mrgss_class_get(mrb, type), args_count, args);
}

mrb_bool mrgss_obj_is_a(mrb_state *mrb, mrb_value obj, const char *class_name ) {
    return mrb_obj_is_kind_of(mrb, obj, mrgss_class_get(mrb, class_name));
}

mrb_bool is_number(mrb_state* mrb, mrb_value obj) {
    return mrb_obj_is_kind_of(mrb, obj, mrb_class_get(mrb, "Fixnum"));
}

mrb_bool is_string(mrb_state* mrb, mrb_value obj) {
    return mrb_obj_is_kind_of(mrb, obj, mrb_class_get(mrb, "String"));
}

mrb_bool is_boolean(mrb_state* mrb, mrb_value obj) {
    return mrb_obj_is_kind_of(mrb, obj, mrb_class_get(mrb, "FalseClass")) ||  mrb_obj_is_kind_of(mrb, obj, mrb_class_get(mrb, "TrueClass"));
}

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
void mrgss_emsc_fetch_file(const char * filename) {
    char* host = emscripten_run_script_string("/.*(?=\\/\\w*)/.exec(window.location.href).join() + '/'");
    char* endpoint = malloc(strlen(host) + strlen(filename) + 1);
	strcpy(endpoint, host);
	strcat(endpoint, filename);
    emscripten_wget(endpoint, filename);
}
#endif