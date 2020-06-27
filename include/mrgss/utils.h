#ifndef MRUBY_MRGSS_UTILS_H
#define MRUBY_MRGSS_UTILS_H
#include <mruby.h>
#include <mrgss.h>
/*
 * MRGSS utils
*/
struct RClass* mrgss_module(mrb_state *mrb);
struct RClass* mrgss_class_new(mrb_state *mrb, const char *name);
struct RClass* mrgss_class_get(mrb_state *mrb, const char* name);
/*
 *  Object Utils
*/
#define SET_IV(name, value) mrgss_iv_set(mrb, self, name,value)
#define GET_IV(name)        mrgss_iv_get(mrb, self, name)
#define GET_IV_FROM(obj, name)        mrgss_iv_get(mrb, obj, name)

mrb_bool is_fixnum(mrb_state* mrb, mrb_value obj);
mrb_bool is_string(mrb_state* mrb, mrb_value obj);
mrb_bool is_boolean(mrb_state* mrb, mrb_value obj);
mrb_bool is_nil(mrb_state* mrb, mrb_value obj);
mrb_bool is_a(mrb_state *mrb, mrb_value obj, const char *class_name);
mrb_value mrgss_instance_new(mrb_state *mrb, const char *type, mrb_int args_count,const mrb_value *args);
void mrgss_iv_set(mrb_state *mrb, mrb_value object, const char* name, mrb_value value);
mrb_value mrgss_iv_get(mrb_state *mrb, mrb_value object, const char* name);

Game* getContext();
Screen* getScreen();

/* file utils */
#ifdef __EMSCRIPTEN__
void mrgss_emsc_fetch_file(const char* filename);
#endif
#endif