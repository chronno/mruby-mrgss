#ifndef MRUBY_MRGSS_SCREEN_H
#define MRUBY_MRGSS_SCREEN_H
#include <mruby.h>
#include <mrgss.h>
#ifdef __EMSCRIPTEN__
#include <GLES2/gl2.h>
#include <GLES3/gl32.h>
#else
#include <gl3w.h>
#endif
#include <glfw3.h>
#include <bmp.h>

/* Create MRuby type */
void create_screen_type(mrb_state* mrb);

typedef struct mrgss_screen { 
    int x, y, w, h;
    int fullscreen;
    char* title;
    Bitmap* icon;
    GLFWwindow* hwnd;
    Renderer* renderer;
} Screen;

int mrgss_window_create(Screen* screen);
void mrgss_window_set_context(Screen* screen, void* context);
void* mrgss_window_get_context(Screen* screen);
void* mrgss_get_context_from_window(GLFWwindow* window);
void mrgss_window_change_position(Screen* screen);
void mrgss_window_change_size(Screen* screen);
void mrgss_window_change_title(Screen* screen);
void mrgss_window_toggle_fullscreen(Screen* screen);
void mrgss_window_change_icon(Screen* screen);
void mrgss_window_set_should_close(Screen* screen, int value);


void dispatch_window_change_position(Game* game, int old_x, int old_y);
void dispatch_window_change_size(Game* game, int width, int height);
void dispatch_window_change_focus(Game* game, int focused);
void dispatch_window_close(Game* game);
#endif