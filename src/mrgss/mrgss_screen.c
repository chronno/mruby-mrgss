#ifdef __EMSCRIPTEN__
#include <GLES2/gl2.h>
#include <GLES3/gl32.h>
#else
#include <gl3w.h>
#endif
#include <glfw3.h>
#include <mrgss.h>
#include <mrgss/screen.h>
#include <bmp.h>

#ifndef __EMSCRIPTEN__
int create_gl_context(Screen* screen) {
    return !gl3wInit();
}
#else 
int create_gl_context(Screen* screen) {
    return 1;
}
#endif

static void on_window_position_change(GLFWwindow* window, int xpos, int ypos) {
    dispatch_window_change_position(glfwGetWindowUserPointer(window), xpos, ypos);
}

static void on_window_size_change(GLFWwindow* window, int width, int height) {
    dispatch_window_change_size(glfwGetWindowUserPointer(window), width, height);
}

static void on_window_focus_change(GLFWwindow* window, int focused) {
    dispatch_window_change_focus(glfwGetWindowUserPointer(window), focused);
}

static void on_window_close(GLFWwindow* window) {
    dispatch_window_close(glfwGetWindowUserPointer(window));
}

static void set_callbacks(Screen* screen) {
    glfwSetWindowPosCallback(screen->hwnd, on_window_position_change);
    glfwSetWindowSizeCallback(screen->hwnd, on_window_size_change);
    glfwSetWindowFocusCallback(screen->hwnd, on_window_focus_change);
    glfwSetWindowCloseCallback(screen->hwnd, on_window_close);
    //glfwSetWindowIconifyCallback // cuando la minimizan
    //glfwSetWindowMaximizeCallback // cuando la maximizan
}


int mrgss_window_create(Screen* screen) {
    screen->hwnd = glfwCreateWindow(screen->w, screen->h, screen->title, NULL, NULL);
    glfwMakeContextCurrent(screen->hwnd);
    set_callbacks(screen);
    mrgss_window_change_size(screen);
    mrgss_window_change_title(screen);
    mrgss_window_change_icon(screen);
    return create_gl_context(screen);
}

void mrgss_window_set_context(Screen* screen, void* context) { glfwSetWindowUserPointer(screen->hwnd, context); }

void* mrgss_window_get_context(Screen* screen) { return glfwGetWindowUserPointer(screen->hwnd); }

void* mrgss_get_context_from_window(GLFWwindow* window) { return glfwGetWindowUserPointer(window); }

void mrgss_window_change_position(Screen* screen) { glfwSetWindowPos(screen->hwnd, screen->x, screen->y); }

void mrgss_window_change_size(Screen* screen) { glfwSetWindowSize(screen->hwnd, screen->w, screen->h); }

void mrgss_window_change_title(Screen* screen) { glfwSetWindowTitle(screen->hwnd, screen->title); }

void mrgss_window_toggle_fullscreen(Screen* screen) {
    #ifndef __EMSCRIPTEN__
    if (screen->fullscreen) {
        glfwSetWindowMonitor(screen->hwnd, glfwGetPrimaryMonitor(), screen->x, screen->y, screen->w, screen->h, GLFW_DONT_CARE);
    } else {
        glfwSetWindowMonitor(screen->hwnd, NULL, screen->x, screen->y, screen->w, screen->h, GLFW_DONT_CARE);
    }
    #endif
}

void mrgss_window_set_should_close(Screen* screen, int value) {
    glfwSetWindowShouldClose(screen->hwnd, value);
}

void mrgss_window_change_icon(Screen* screen) {
    if (screen->hwnd && screen->icon) {
        GLFWimage icons[1];
        icons[0].pixels = screen->icon->data;
        icons[0].width = screen->icon->w;
        icons[0].height = screen->icon->h;
        glfwSetWindowIcon(screen->hwnd, 1, icons);
    }
    
}