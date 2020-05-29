#include <stdlib.h>
#include <mruby.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#include <gl/gl3w.h>
#endif
#include <GLFW/glfw3.h>
#include <mrgss.h>
#include <mrgss/structs.h>

static void configure_window() {
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}


int create_screen(GameContext* game, mrb_int width, mrb_int height, char* title) {
    if(glfwInit()) { 
        configure_window();
        game->window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (game->window != NULL) {
            glfwMakeContextCurrent(game->window);
            #ifndef __EMSCRIPTEN__
            if(gl3wInit()) { return FALSE; }
            #endif    
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glfwSetWindowUserPointer(game->window, game);
            game->renderer = mrb_malloc(game->mrb, sizeof(GameRenderer));
            initialize_renderer(game);
            return TRUE;            
        }
    }
    return FALSE;
}

void destroy_screen(GameContext* game) {
    glfwDestroyWindow(game->window);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // mrb_value keyboard = mrb_obj_value(mrb_module_get_under(MRUBY, mrgss_module(MRUBY), "Keyboard"));
    // mrb_funcall(MRUBY, keyboard, "update", 2, mrb_fixnum_value(key),mrb_fixnum_value(action));
}

static void character_callback(GLFWwindow* window, unsigned int codepoint) {
    // mrb_value keyboard = mrb_obj_value(mrb_module_get_under(MRUBY, mrgss_module(MRUBY), "Keyboard"));
    // mrb_funcall(MRUBY, keyboard, "something", 1, mrb_fixnum_value(codepoint));
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    // mrb_value mouse = mrb_obj_value(mrb_module_get_under(MRUBY, mrgss_module(MRUBY), "Mouse"));
    // mrb_funcall(MRUBY, mouse, "update_position", 2, mrb_fixnum_value(xpos), mrb_fixnum_value(ypos));
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    // mrb_value mouse = mrb_obj_value(mrb_module_get_under(MRUBY, mrgss_module(MRUBY), "Mouse"));
    // mrb_funcall(MRUBY, mouse, "update_buttons", 2, mrb_fixnum_value(button), mrb_fixnum_value(action));
}

static void main_loop(GameContext* game) {
    if (!glfwWindowShouldClose(game->window)) {
        glfwPollEvents();
        mrb_funcall(game->mrb, game->game, "update", 0);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //should render here
        renderer_draw(game);
        glfwSwapBuffers(game->window);
    } else {
        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        #endif
    }
}



void show_screen(GameContext* game) {
    glfwSetKeyCallback(game->window, key_callback);
    glfwSetCharCallback(game->window, character_callback);
    glfwSetCursorPosCallback(game->window, cursor_position_callback);
    glfwSetMouseButtonCallback(game->window, mouse_button_callback);
    glfwShowWindow(game->window);
    mrb_funcall(game->mrb, game->game, "start", 0);
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(main_loop, game, 0, TRUE);
    #else 
    while(!glfwWindowShouldClose(game->window)) {       
        main_loop(game);
    }
    #endif
    destroy_screen(game);
}

