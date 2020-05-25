#include <stdlib.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#include <GL/gl3w.h>
#endif
#include <GLFW/glfw3.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mrgss/structs.h>
#include <mrgss/types/screen.h>

static void main_loop(void* p) {
    MR_Screen* screen = (MR_Screen*) p;
    if (!window_should_close(screen)) {
        window_update(screen);
        window_swapbuffers(screen);
    } else {
        screen->disposed = TRUE;
        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        #endif
    }
}

void game_init(mrb_state *mrb, mrb_value game, mrb_value screen) {
    MR_Screen *cscreen = DATA_PTR(screen);    
    window_show(cscreen);
    printf("window shown\n");
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(main_loop, cscreen, -1, 0);
    #else 
    while(!cscreen->disposed) {       
        main_loop(cscreen);
    }
    #endif
}
