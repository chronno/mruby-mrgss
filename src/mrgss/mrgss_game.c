#include <stdlib.h>
#include <stdio.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mrgss.h>
#include <mrgss/game.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <GLES2/gl2.h>
#include <GLES3/gl32.h>
#else
#include <gl3w.h>
#endif
#include <glfw3.h>

static void start_game() {
    Game* game = getContext();
    mrb_funcall(game->mrb, game->game, "start", 0);
}

static void update_game() {
    Game* game = getContext();
    mrb_funcall(game->mrb, game->game, "update", 0);
}

static void initialize(mrb_state* mrb, mrb_value self, Screen* screen) {
    if (!glfwInit()) { mrb_raise(mrb, E_RUNTIME_ERROR, "fallo glfwinit"); }
    if (!mrgss_window_create(screen)) { mrb_raise(mrb, E_RUNTIME_ERROR, "fallo create window"); } 
    mrgss_window_set_context(screen, DATA_PTR(self));
    mrgss_window_change_position(screen);
    mrgss_window_toggle_fullscreen(screen);
    initialize_renderer();
    start_game();
}

static void main_loop() {
    if (!glfwWindowShouldClose( getScreen()->hwnd )) {
        glfwPollEvents();
        update_game();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        prepare_renderer();
        glfwSwapBuffers(getScreen()->hwnd);
        //if renderer needs to draw
            //draw
    } else {
        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        glfwDestroyWindow(getScreen()->hwnd);
        glfwTerminate();
        #endif
    }
}



void mrgss_game_start(mrb_state* mrb, mrb_value self) {
    Screen* screen = DATA_PTR(GET_IV("@screen"));
    initialize(mrb, self, screen);
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, TRUE);
    #else 
    while(!glfwWindowShouldClose(screen->hwnd)) {       
        main_loop();
    }
    glfwDestroyWindow(screen->hwnd);
    glfwTerminate();
    #endif
}