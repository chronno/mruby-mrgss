#include <stdlib.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include <mruby.h>
#include <mruby/data.h>
#include <mrgss/structs.h>
#include <mrgss/types/game.h>
#include <raylib.h>

void main_loop(void* p) {
    MR_Context* context = (MR_Context*) p;
    if(!WindowShouldClose()) {
        mrb_funcall(context->mrb, context->game, "update", 0);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        mrb_funcall(context->mrb, context->game, "render", 0);
        DrawText(context->screen->title, 0, 0, 20, LIGHTGRAY);
        EndDrawing();
    } else {
        context->screen->disposed = TRUE;
        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        #endif
    }
    sprintf(context->screen->title, "%d", GetFPS());
}

void game_init(MR_Context* game_context) {
    InitWindow(game_context->screen->width, game_context->screen->height, game_context->screen->title);
    mrb_funcall(game_context->mrb, game_context->game, "start", 0);
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(main_loop, game_context, 0, TRUE);
    #else 
    while(!game_context->screen->disposed) {       
        main_loop(game_context);
    }
    #endif
    CloseWindow();
}
