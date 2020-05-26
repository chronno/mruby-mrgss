#include <stdlib.h>
#include <string.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include <raylib.h>
#include <mrgss.h>
#include <mrgss/utils.h>
#include <mrgss/structs.h>

static void mrgss_bitmap_free(mrb_state *mrb, void *p) {
    if (p) {       
        MR_Bitmap* img = (MR_Bitmap*) p;
        UnloadImage(img->image);
        mrb_free(mrb, p);
    }
}

static const struct mrb_data_type bitmap_data_type = {
  "MRGSS::Bitamp", mrgss_bitmap_free
};

void onload(const char * filename) {
    printf("file %s was loaded", filename);
}

void onerror(const char * filename) {
    printf("file %s failed to load", filename);
}

static mrb_value mrgss_bitmap_initialize(mrb_state* mrb, mrb_value self) {
    mrb_value param, color;
    mrb_int args, height;
    const char * filename;
    Color* cColor;
    MR_Bitmap* image;
    args = mrb_get_args(mrb, "o|io", &param, &height, &color);
    image = mrb_malloc(mrb, sizeof(MR_Bitmap));
    switch (args) {
    case 1:
        filename = mrb_str_to_cstr(mrb, param);
        #ifdef __EMSCRIPTEN__
        // char* host = emscripten_run_script_string("/.*(?=\\/\\w*)/.exec(window.location.href).join() + '/'");
        // char* endpoint = malloc(strlen(host) + strlen(filename) + 1);
        // strcpy(endpoint, host);
        // strcat(endpoint, filename);
        //emscripten_async_wget(filename, filename, onload, onerror);
        emscripten_wget(filename, filename);
        //mrgss_emsc_fetch_file(filename);
        #endif
        image->image = LoadImage(filename);
        image->name = filename;
        break;
    case 3:
        cColor = DATA_PTR(color);
        image->image = GenImageColor(mrb_int(mrb, param), height, *cColor); 
    default:
        mrb_free(mrb, image);
        mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_NUMBER_ARGS);
        break;
    }
    DATA_PTR(self) = image;
    DATA_TYPE(self) = &bitmap_data_type;
    return self;
}


void mrgss_bitmap_init(mrb_state *mrb) {
    struct RClass* mrb_bitmap = mrgss_class_new(mrb, "Bitmap");
    mrb_define_method(mrb, mrb_bitmap, "initialize", mrgss_bitmap_initialize, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(2));
}