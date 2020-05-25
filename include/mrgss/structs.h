#ifndef MRUBY_MRGSS_TYPES_H
#define MRUBY_MRGSS_TYPES_H
#include <mruby.h>
#ifndef __EMSCRIPTEN__
#include <GL/gl3w.h>
#endif
#include <GLFW/glfw3.h>
/*
 * Usefull 
*/
typedef struct mrgss_context {
    mrb_state *mrb;
    mrb_value game;
} MR_Context;
/*
 * Base Structures
*/ 
typedef struct mrgss_rectangle {
    mrb_int x, y, w, h;
} MR_Rect;

typedef struct mrgss_color {
    mrb_int r, g, b, a;
} MR_Color;

typedef struct mrgss_point {
    mrb_int x, y;
} MR_Point;

typedef struct mrgss_screen {
    GLFWwindow *window;
    GLboolean fullscreen, disposed;
    GLuint width;
    GLuint height;
    GLchar *title;
} MR_Screen;

#endif