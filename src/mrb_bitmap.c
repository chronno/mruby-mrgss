#include <mruby.h>
#include <mrb_mrgss.h>
#include <mrgss/gl.h>
#include <mrgss/structs.h>
#include <mrgss/utils.h>

static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    char* filename;
    Bitmap* bitmap;
    mrb_get_args(mrb, "z", &filename);
    bitmap = mrb_malloc(mrb, sizeof(Bitmap));
    bitmap_from_file(bitmap, filename);
    if (bitmap->data) {
        MRG_SET_PROP("@width", mrb_fixnum_value(bitmap->width));
        MRG_SET_PROP("@height", mrb_fixnum_value(bitmap->height));
    } else {
        mrb_free(mrb, bitmap);
        mrb_raise(mrb, E_RUNTIME_ERROR, "Fallo la carga del archivo");
    }
    return self;
}

void create_bitmap_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Bitmap");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(4));
}