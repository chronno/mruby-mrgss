#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>
#include <mrgss.h>
#include <mrgss/bitmap.h>
#include <bmp.h>

static void mrb_bitmap_free(mrb_state* mrb, void* data) {
    if (data) {
        Bitmap* bmp = (Bitmap*) data;
        bm_free(bmp);
    }
}


static const struct mrb_data_type bitmap_data_type = { "MRGSS::Bitmap", mrb_bitmap_free };

static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    mrb_value arg1;
    mrb_int h, argc;
    Bitmap* bitmap;
    char* filename;
    argc = mrb_get_args(mrb, "o|i", &arg1, &h);   
    switch (argc) {
    case 1:
        if (is_string(mrb, arg1)) {
            filename = mrb_string_value_ptr(mrb, arg1);
            #ifdef __EMSCRIPTEN__
            mrgss_emsc_fetch_file(filename);
            #endif
            bitmap = bm_load_stb(filename);
            if (!bitmap->data) {
                mrb_raise(mrb, E_RUNTIME_ERROR, "could not load the image");
                return mrb_nil_value();
            }
        } 
        break;
    case 2:
        if (is_fixnum(mrb, arg1)) {
            bitmap = bm_create((int)mrb_int(mrb, arg1), (int)h);
            if (!bitmap->data) {
                mrb_raise(mrb, E_RUNTIME_ERROR, "could not create the image");
                return mrb_nil_value();
            }
        }
        break;
    default:
        mrb_raise(mrb, E_ARGUMENT_ERROR, "Wrong type of arguments");
        return mrb_nil_value();
        break;
    }
    DATA_PTR(self) = bitmap;
    DATA_TYPE(self) = &bitmap_data_type;
    return self;
}

void create_bitmap_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Bitmap");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_OPT(2));
}