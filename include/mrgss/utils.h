#ifndef MRUBY_MRGSS_UTILS_H
#define MRUBY_MRGSS_UTILS_H
#include <mruby.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#define MRG_SET_PROP(name, value)\
    mrgss_iv_set(mrb, self, name,value)

#define MRG_GET_PROP(name)\
    mrgss_iv_get(mrb, self, name)

#define MRG_GET_PROP_FROM(target, name)\
    mrgss_iv_get(mrb, target, name)

#define MRG_GET_PROP_AS_FLOAT(target, name)\
    mrb_float(mrgss_iv_get(mrb, target, name))
/*
 * MRGSS utils
*/
struct RClass* mrgss_module(mrb_state *mrb);
struct RClass* mrgss_class_new(mrb_state *mrb, const char *name);
struct RClass* mrgss_class_get(mrb_state *mrb, const char* name);
mrb_value mrgss_instance_new(mrb_state *mrb, const char *type, mrb_int args_count,const mrb_value *args);
/*
 *  Object Utils
*/
mrb_bool is_number(mrb_state* mrb, mrb_value obj);
mrb_bool is_string(mrb_state* mrb, mrb_value obj);
mrb_bool is_boolean(mrb_state* mrb, mrb_value obj);
mrb_bool mrgss_obj_is_a(mrb_state *mrb, mrb_value obj, const char *class_name );
/*
 *  Instance Variables Utils
*/
mrb_value mrgss_iv_get(mrb_state *mrb, mrb_value object, const char* name);
void mrgss_iv_set(mrb_state *mrb, mrb_value object, const char* name, mrb_value value);
/*
 *  Emscripten Utils
*/
#ifdef __EMSCRIPTEN__
void mrgss_emsc_fetch_file(const char * filename);
#endif

#endif