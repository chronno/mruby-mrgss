#include <mrgss.h>

static void bitmap_free(mrb_state *mrb, void *p) {
    if (p) {
        Bitmap* bitmap = (Bitmap*) p;
        free(bitmap->data);
        mrb_free(mrb, bitmap);
    }
}

struct mrb_data_type const bitmap_data_type = {"MRGSS::Bitmap", bitmap_free};

static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    char* filename;
    Bitmap* bitmap;
    mrb_get_args(mrb, "z", &filename);
    bitmap = mrb_malloc(mrb, sizeof(Bitmap));
    bitmap_from_file(bitmap, filename);
    if (bitmap->data) {
        DATA_PTR(self) = bitmap;
        DATA_TYPE(self) = &bitmap_data_type;
    } else {
        mrb_free(mrb, bitmap);
        mrb_raise(mrb, E_RUNTIME_ERROR, "Fallo la carga del archivo");
    }
    return self;
}

static mrb_value get_width(mrb_state* mrb, mrb_value self) {
    Bitmap* bmp = DATA_PTR(self);
    return mrb_fixnum_value(bmp->width);
}

static mrb_value get_height(mrb_state* mrb, mrb_value self) {
    Bitmap* bmp = DATA_PTR(self);
    return mrb_fixnum_value(bmp->height);
}

void create_bitmap_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Bitmap");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(4));
    mrb_define_method(mrb, type, "width", get_width, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "height", get_height, MRB_ARGS_NONE());
}