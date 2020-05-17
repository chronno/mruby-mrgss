#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>

#include <GLFW/glfw3.h>
#include <raylib.h>

#include <mrgss.h>
#include <mrgss/screen.h>

#define MRGSS_MODULE mrb_module_get(mrb, "MRGSS")

static void mrgss_screen_free(mrb_state *mrb, void *p) {
    if (p) {        
        mrb_free(mrb, p);
    }
}

static const struct mrb_data_type screen_data_type = {
  "MRGSS::Screen", mrgss_screen_free
};

static mrb_value mrgss_screen_initialize(mrb_state* mrb, mrb_value self) {
    Screen* screen;
    mrb_value window_rect;
    Rectangle* cRect;
    char *title;
    mrb_get_args(mrb, "oz", &window_rect, &title);
    screen = mrb_malloc(mrb, sizeof(screen));
    screen->screen_rect = mrb_malloc(mrb, sizeof(Rectangle*));
    if (mrb_obj_is_instance_of(mrb, window_rect, mrb_class_get_under(mrb, MRGSS_MODULE, "Rectangle"))) {
        screen->title = title;
        cRect = DATA_PTR(window_rect);
        screen->screen_rect = cRect;
        screen->disposed = FALSE;
        DATA_PTR(self) = screen;
        DATA_TYPE(self) = &screen_data_type;
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_TYPE_ARGS);
    }
    return self;
}

static mrb_value mrgss_screen_x_get(mrb_state *mrb, mrb_value self) {
  Screen* value = DATA_PTR(self);
  return mrb_fixnum_value(value->screen_rect->x);
}

static mrb_value mrgss_screen_x_set(mrb_state *mrb, mrb_value self) {
  mrb_value new_value;
  Screen *value = DATA_PTR(self);
  mrb_get_args(mrb, "o", &new_value);
  value->screen_rect->x = mrb_int(mrb, new_value);
  SetWindowPosition(value->screen_rect->x, value->screen_rect->y);
  return mrb_nil_value();
}

static mrb_value mrgss_screen_y_get(mrb_state *mrb, mrb_value self) {
  Screen *value = DATA_PTR(self);
  return mrb_fixnum_value(value->screen_rect->y);
}

static mrb_value mrgss_screen_y_set(mrb_state *mrb, mrb_value self) {
  mrb_value new_value;
  Screen *value = DATA_PTR(self);
  mrb_get_args(mrb, "o", &new_value);
  value->screen_rect->y = mrb_int(mrb, new_value);
  SetWindowPosition(value->screen_rect->x, value->screen_rect->y);
  return mrb_nil_value();
}

static mrb_value mrgss_screen_width_get(mrb_state *mrb, mrb_value self) {
  Screen *value = DATA_PTR(self);
  return mrb_fixnum_value(value->screen_rect->width);
}

static mrb_value mrgss_screen_width_set(mrb_state *mrb, mrb_value self) {
  mrb_value new_value;
  Screen *value = DATA_PTR(self);
  mrb_get_args(mrb, "o", &new_value);
  value->screen_rect->width = mrb_int(mrb, new_value);
  SetWindowSize(value->screen_rect->width, value->screen_rect->height);
  return mrb_nil_value();
}

static mrb_value mrgss_screen_height_get(mrb_state *mrb, mrb_value self) {
  Screen *value = DATA_PTR(self);
  return mrb_fixnum_value(value->screen_rect->height);
}

static mrb_value mrgss_screen_height_set(mrb_state *mrb, mrb_value self) {
  mrb_value new_value;
  Screen *value = DATA_PTR(self);
  mrb_get_args(mrb, "o", &new_value);
  value->screen_rect->height = mrb_int(mrb, new_value);
  SetWindowSize(value->screen_rect->width, value->screen_rect->height);
  return mrb_nil_value();
}

static mrb_value mrgss_screen_title_get(mrb_state *mrb, mrb_value self) {
  Screen *value = DATA_PTR(self);
  return mrb_str_new_cstr(mrb, value->title);
}

static mrb_value mrgss_screen_title_set(mrb_state *mrb, mrb_value self) {
  Screen *value = DATA_PTR(self);
  mrb_get_args(mrb, "z", &value->title);
  SetWindowTitle(value->title);
  return mrb_nil_value();
}

static mrb_value mrgss_screen_rect_get(mrb_state *mrb, mrb_value self) {
  Screen *value = DATA_PTR(self);
  return create_rectangle_from(mrb, value->screen_rect->x, value->screen_rect->y, value->screen_rect->width, value->screen_rect->height);
}

static mrb_value mrgss_screen_rect_set(mrb_state *mrb, mrb_value self) {
  mrb_value mrbRect;
  Rectangle* cRect;
  Screen *value = DATA_PTR(self);
  mrb_get_args(mrb, "o", &mrbRect);
  cRect = DATA_PTR(mrbRect);
  value->screen_rect = cRect;
  return mrb_nil_value();
}

static mrb_value mrgss_screen_show(mrb_state* mrb, mrb_value self) {
    Screen* cScreen = DATA_PTR(self);
    InitWindow(cScreen->screen_rect->width, cScreen->screen_rect->height, cScreen->title);
    SetWindowPosition(cScreen->screen_rect->x, cScreen->screen_rect->y);
    cScreen->window = GetWindowHandle();
    SetTargetFPS(60);   
  return mrb_nil_value();
}

static mrb_value mrgss_screen_update(mrb_state* mrb, mrb_value self) {
  Screen* cScreen = DATA_PTR(self);
  if(cScreen->disposed) {
    CloseWindow();
    return mrb_nil_value();
  }
  if (!WindowShouldClose()) {
        BeginDrawing();
            DrawFPS(10, 10);
            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    } else {
      cScreen->disposed = TRUE;
    }
    return mrb_nil_value();
}

static mrb_value mrgss_screen_is_disposed(mrb_state* mrb, mrb_value self) {
  Screen* cScreen = DATA_PTR(self);
  if (cScreen->disposed) {
    return mrb_true_value();
  } else {
    return mrb_false_value();
  }
}

void mrgss_screen_init(mrb_state *mrb) {
    struct RClass* mrb_screen = mrgss_create_class(mrb, "Screen");
    mrb_define_method(mrb, mrb_screen, "initialize", mrgss_screen_initialize, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_screen, "x", mrgss_screen_x_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_screen, "x=", mrgss_screen_x_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_screen, "y", mrgss_screen_y_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_screen, "y=", mrgss_screen_y_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_screen, "width", mrgss_screen_width_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_screen, "width=", mrgss_screen_width_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_screen, "height", mrgss_screen_height_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_screen, "height=", mrgss_screen_height_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_screen, "title", mrgss_screen_title_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_screen, "title=", mrgss_screen_title_set, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb_screen, "rect", mrgss_screen_rect_get, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_screen, "rect=", mrgss_screen_rect_set, MRB_ARGS_REQ(1));

    mrb_define_method(mrb, mrb_screen, "disposed?", mrgss_screen_is_disposed, MRB_ARGS_NONE());

    mrb_define_method(mrb, mrb_screen, "show", mrgss_screen_show, MRB_ARGS_NONE());
    mrb_define_method(mrb, mrb_screen, "update", mrgss_screen_update, MRB_ARGS_NONE());
}