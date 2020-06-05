#include <mrgss.h>


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
            return TRUE;            
        }
    }
    return FALSE;
}

void destroy_screen(GameContext* game) {
    glfwDestroyWindow(game->window);
}

static void character_callback(GLFWwindow* window, unsigned int codepoint) {
    GameContext* context = glfwGetWindowUserPointer(window);
    mrb_value keyboard = mrb_obj_value(mrb_module_get_under(context->mrb, mrgss_module(context->mrb), "Keyboard"));
    mrb_funcall(context->mrb, keyboard, "something", 1, mrb_fixnum_value(codepoint));
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    GameContext* context = glfwGetWindowUserPointer(window);
    mrb_value mouse = mrb_obj_value(mrb_module_get_under(context->mrb, mrgss_module(context->mrb), "Mouse"));
    mrb_funcall(context->mrb, mouse, "update_position", 2, mrb_fixnum_value(xpos), mrb_fixnum_value(ypos));
}

static void update_input(GameContext *context) {
    int i, state;
    mrb_value mouse = mrb_obj_value(mrb_module_get_under(context->mrb, mrgss_module(context->mrb), "Mouse"));
    mrb_value keyboard = mrb_obj_value(mrb_module_get_under(context->mrb, mrgss_module(context->mrb), "Keyboard"));
    for (i = 0; i < 512; i++) {
        state = glfwGetKey(context->window, i);
        mrb_funcall(context->mrb, keyboard, "update", 2, mrb_fixnum_value(i),mrb_fixnum_value(state));
    }
    for (i = 0; i < 8; i++) {
        state = glfwGetMouseButton(context->window, i);
        mrb_funcall(context->mrb, mouse, "update_buttons", 2, mrb_fixnum_value(i), mrb_fixnum_value(state));
    }
}

static void main_loop(GameContext* game) {
    int toRender = 0;
    double start = glfwGetTime();
    if (!glfwWindowShouldClose(game->window)) {
        glfwPollEvents();
        update_input(game);
        mrb_funcall(game->mrb, game->game, "update", 0);
        toRender = prepare_renderer(game);
        if (toRender > 0) {
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            renderer_draw(game, toRender);
            glfwSwapBuffers(game->window);
        }
    } else {
        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        #endif
    }
    double end = glfwGetTime();
    // printf("Cicle time: %f\n", end - start);
}


void show_screen(GameContext* game) {
    glfwSetWindowUserPointer(game->window, game);
    glfwSetCharCallback(game->window, character_callback);
    glfwSetCursorPosCallback(game->window, cursor_position_callback);
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

