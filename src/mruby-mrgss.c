
#include <stdlib.h>
#include <string.h>
#include <mruby.h>
#include <mruby/irep.h>
#include <mrgss/utils.h>

int main() {
    mrb_state *mrb = mrb_open();
    #ifdef __EMSCRIPTEN__
    mrgss_emsc_fetch_file("main.rb");
    #endif
    FILE* file = fopen("main.rb", "rb");
    mrb_load_file(mrb, file);
    mrb_close(mrb);
    fclose(file);
    return 0;
}

