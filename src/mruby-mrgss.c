
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <mruby.h>
#include <mruby/irep.h>
#include <mrgss.h>




int main() {
    mrb_state *mrb = mrb_open();
    #ifdef __EMSCRIPTEN__
    emscripten_wget(get_endpoint("main.rb"), "main.rb");
    #endif
    FILE* file = fopen("main.rb", "rb");
    mrb_load_file(mrb, file);
    mrb_close(mrb);
    free(file);
    return 0;
}

