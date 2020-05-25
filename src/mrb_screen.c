#include <mruby.h>
#include <mruby/data.h>
#include <mrgss.h>
#include <mrgss/utils.h>
#include <mrgss/structs.h>
#include <mrgss/types/screen.h>

static void screen_free(mrb_state *mrb, void *p) {
    if (p) {
        MR_Screen* screen = (MR_Screen*) p;
        if (screen->window) {
            window_destroy(screen);
        }
        mrb_free(mrb, screen);
    }
}

static const struct mrb_data_type screen_data_type = {
  "MRGSS::Screen", screen_free
};

static mrb_value mrgss_screen_initialize(mrb_state* mrb, mrb_value self) {
    MR_Screen* screen;
    mrb_value rect;
    char *title;
    mrb_bool fullscreen;
    mrb_int args;
    args = mrb_get_args(mrb, "zo|b", &title, &rect, &fullscreen);
    screen = mrb_malloc(mrb, sizeof(screen));
    if(args == 3) { fullscreen = FALSE; }
    if (window_create(screen, title, DATA_PTR(rect), fullscreen)) {
        DATA_PTR(self) = screen;
        DATA_TYPE(self) = &screen_data_type;
    } else {
        mrb_free(mrb, screen);
        mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_TYPE_ARGS);  
        return mrb_nil_value();
    }
    return self;
}

static mrb_value mrgss_screen_show(mrb_state* mrb, mrb_value self) {
    window_show(DATA_PTR(self));
    return mrb_nil_value();
}

static mrb_value mrgss_screen_update(mrb_state* mrb, mrb_value self) {
    window_update(DATA_PTR(self));
    window_swapbuffers(DATA_PTR(self));
    return mrb_nil_value();
}

void mrgss_screen_init(mrb_state* mrb) {
    struct RClass* point = mrgss_class_new(mrb, "Screen");
    mrb_define_method(mrb, point, "initialize", mrgss_screen_initialize, MRB_ARGS_REQ(2)|MRB_ARGS_OPT(1));
    mrb_define_method(mrb, point, "show", mrgss_screen_show, MRB_ARGS_NONE());
    mrb_define_method(mrb, point, "update", mrgss_screen_update, MRB_ARGS_NONE());
}