#ifndef MRUBY_MRGSS_SCREEN_H
#define MRUBY_MRGSS_SCREEN_H

#include <mruby.h>
#include <raylib.h>
#include <GLFW/glfw3.h>

typedef struct mrgss_screen {
    const char* title;
    Rectangle* screen_rect;
    mrb_bool fullscreen, hide, disposed;
    Image windowIcon;
    GLFWwindow* window;
} Screen;

#endif