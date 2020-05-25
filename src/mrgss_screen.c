#ifndef __EMSCRIPTEN__
#include <GL/gl3w.h>
#endif
#include <GLFW/glfw3.h>

#include <mrgss/structs.h>
#include <mrgss/types/screen.h>

static void configure_window() {
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

int window_create(MR_Screen *buffer,const char* title, MR_Rect* rect, GLboolean fullscreen) {
    if(glfwInit()) {
        configure_window();
        if(fullscreen){
            buffer->window = glfwCreateWindow(rect->w, rect->h, title, glfwGetPrimaryMonitor(), NULL);
        } else {
            buffer->window = glfwCreateWindow(rect->w, rect->h, title, NULL, NULL);
        }
        buffer->width = rect->w;
        buffer->height = rect->h;
        buffer->disposed = FALSE;
        if(buffer->window){
            glfwMakeContextCurrent(buffer->window);
            #ifndef __EMSCRIPTEN__
            gl3wInit();
            #endif
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            return TRUE;
        }
        
    }
    return FALSE;
}

void window_set_context(MR_Screen* screen, MR_Context* context) {
    glfwSetWindowUserPointer(screen->window, context);
}

MR_Context* window_get_context(GLFWwindow* window) {
    return glfwGetWindowUserPointer(window);
}

void window_show(MR_Screen *screen) {
    glfwShowWindow(screen->window);
}

void window_update(MR_Screen *screen) {
    glfwPollEvents();
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void window_swapbuffers(MR_Screen *screen) {
    glfwSwapBuffers(screen->window);
}

int window_should_close(MR_Screen* screen) {
    return glfwWindowShouldClose(screen->window);
}

void window_destroy(MR_Screen *screen) {
    glfwDestroyWindow(screen->window);
}