#include <mruby.h>
#include <mruby/data.h>
#include <mrgss.h>
#include <mrgss/screen.h>

static void mrb_screen_free(mrb_state* mrb, void* data) {
    if (data) {
        Screen* screen = (Screen*) data;
        mrb_free(mrb, screen);
    }
}

static const struct mrb_data_type screen_data_type = { "MRGSS::Screen", mrb_screen_free };

static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    mrb_value rectars[4];
    Screen* screen = mrb_malloc(mrb, sizeof(Screen));
    screen->x = 200;
    screen->y = 200;
    screen->w = 640;
    screen->h = 480;
    screen->title = "";
    screen->fullscreen = FALSE;
    DATA_PTR(self) = screen;
    DATA_TYPE(self) = &screen_data_type;
    rectars[0] = mrb_fixnum_value(0);
    rectars[1] = mrb_fixnum_value(0);
    rectars[2] = mrb_fixnum_value(640);
    rectars[3] = mrb_fixnum_value(480);
    SET_IV("@viewport", mrgss_instance_new(mrb, "Viewport", 4, rectars));
    return self;
}

static mrb_value set_x(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Screen* screen;
    mrb_get_args(mrb, "i", &value);
    screen = DATA_PTR(self);
    screen->x = (int) value;
    mrgss_window_change_position(screen);
    return self;
}

static mrb_value set_y(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Screen* screen;
    mrb_get_args(mrb, "i", &value);
    screen = DATA_PTR(self);
    screen->y = (int) value;
    mrgss_window_change_position(screen);
    return self;
}

static mrb_value set_w(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Screen* screen;
    mrb_get_args(mrb, "i", &value);
    screen = DATA_PTR(self);
    screen->w = (int) value;
    mrgss_window_change_size(screen);
    return self;
}

static mrb_value set_h(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Screen* screen;
    mrb_get_args(mrb, "i", &value);
    screen = DATA_PTR(self);
    screen->h = (int) value;
    mrgss_window_change_size(screen);
    return self;
}

static mrb_value set_title(mrb_state* mrb, mrb_value self) {
    char* value;
    Screen* screen;
    mrb_get_args(mrb, "z", &value);
    screen = DATA_PTR(self);
    screen->title = value;
    mrgss_window_change_title(screen);
    return self;
}

static mrb_value set_fullscreen(mrb_state* mrb, mrb_value self) {
    mrb_bool value;
    Screen* screen;
    mrb_get_args(mrb, "b", &value);
    screen = DATA_PTR(self);
    screen->fullscreen = value;
    mrgss_window_toggle_fullscreen(screen);
    return self;
}

static mrb_value set_icon(mrb_state* mrb, mrb_value self) {
    mrb_value value;
    Screen* screen;
    mrb_get_args(mrb, "o", &value);
    screen = DATA_PTR(self);
    if (is_a(mrb, value, "Bitmap")){
        screen->icon = DATA_PTR(value);
        mrgss_window_change_icon(screen);
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "Bitmap required");
    }
    return self;
}

static mrb_value set_on_window_change_position(mrb_state* mrb, mrb_value self) {
    mrb_value value;
    mrb_get_args(mrb, "o", &value);
    SET_IV("@on_change_position", value);
    return self;
}

static mrb_value set_on_window_change_size(mrb_state* mrb, mrb_value self) {
    mrb_value value;
    mrb_get_args(mrb, "o", &value);
    SET_IV("@on_change_size", value);
    return self;
}

static mrb_value set_on_window_change_focus(mrb_state* mrb, mrb_value self) {
    mrb_value value;
    mrb_get_args(mrb, "o", &value);
    SET_IV("@on_change_focus", value);
    return self;
}

static mrb_value set_on_window_close(mrb_state* mrb, mrb_value self) {
    mrb_value value;
    mrb_get_args(mrb, "o", &value);
    SET_IV("@on_close", value);
    return self;
}

static mrb_value get_viewport(mrb_state* mrb, mrb_value self) {
    return GET_IV("@viewport");
}

void dispatch_window_change_position(Game* game, int x, int y) {
    mrb_value self = game->game;
    mrb_state* mrb = game->mrb;
    mrb_value screen = GET_IV("@screen");
    Screen* cscreen = DATA_PTR(screen);
    cscreen->x = x;
    cscreen->y = y;
    mrb_value callbck = GET_IV_FROM(screen, "@on_change_position");
    if (is_nil(mrb, callbck)){ return; }
    mrb_funcall(mrb, callbck, "call", 2, mrb_fixnum_value(x), mrb_fixnum_value(y));
}

void dispatch_window_change_size(Game* game, int width, int height) {
    mrb_value self = game->game;
    mrb_state* mrb = game->mrb;
    mrb_value screen = GET_IV("@screen");
    Screen* cscreen = DATA_PTR(screen);
    cscreen->w = width;
    cscreen->h = height;
    mrb_value callbck = GET_IV_FROM(screen, "@on_change_size");
    if (is_nil(mrb, callbck)){ return; }
    mrb_funcall(mrb, callbck, "call", 2, mrb_fixnum_value(width), mrb_fixnum_value(height));
}

void dispatch_window_change_focus(Game* game, int focused) {
    mrb_value self = game->game;
    mrb_state* mrb = game->mrb;
    mrb_value screen = GET_IV("@screen");
    mrb_value callbck = GET_IV_FROM(screen, "@on_change_focus");
    if (is_nil(mrb, callbck)){ return; }
    mrb_value focus = focused ? mrb_true_value() : mrb_false_value();
    mrb_funcall(mrb, callbck, "call", 1, focus);
}

void dispatch_window_close(Game* game) {
    mrb_value self = game->game;
    mrb_state* mrb = game->mrb;
    mrb_value screen = GET_IV("@screen");
    mrb_value callbck = GET_IV_FROM(screen, "@on_close");
    if (is_nil(mrb, callbck)){ return; }
    mrb_value should_close = mrb_funcall(mrb, callbck, "call", 0);
    if (!is_boolean(mrb, should_close)) { should_close = mrb_true_value(); }
    mrgss_window_set_should_close(DATA_PTR(screen), mrb_bool(should_close));
}


void create_screen_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Screen");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(3));
    mrb_define_method(mrb, type, "x=", set_x, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "y=", set_y, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "width=", set_w, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "height=", set_h, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "title=", set_title, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "fullscreen=", set_fullscreen, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "icon=", set_icon, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "on_move=", set_on_window_change_position, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "on_resize=", set_on_window_change_size, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "on_focus=", set_on_window_change_focus, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "on_close=", set_on_window_close, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "viewport", get_viewport, MRB_ARGS_REQ(1));
}