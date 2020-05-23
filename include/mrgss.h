#include <mruby.h>
#ifndef MRUBY_MRGSS_H
#define MRUBY_MRGSS_H

typedef struct mrgss_context {
    mrb_state* mrb;
    mrb_value screen;
    mrb_value game;
} MR_Context;
//UTIL
static const char* WRONG_NUMBER_ARGS = "Wrong number of arguments";
static const char* WRONG_TYPE_ARGS = "Wrong type of arguments";
struct RClass* mrgss_module_init(mrb_state *mrb);
struct RClass* mrgss_module(mrb_state *mrb);
struct RClass* mrgss_create_class(mrb_state *mrb, const char *name);
struct RClass* mrgss_get_class(mrb_state *mrb, const char* name);
mrb_bool mrgss_obj_is_a(mrb_state *mrb, mrb_value obj, const char* name);

mrb_bool is_number(mrb_state* mrb, mrb_value obj);

mrb_value mrgss_iv_get(mrb_state *mrb, mrb_value object, const char* name);
void mrgss_iv_create(mrb_state *mrb, mrb_value object, const char* name, mrb_value value);

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
const char* get_endpoint(const char* file);
#endif

#endif //MRUBY_MRGSS_H