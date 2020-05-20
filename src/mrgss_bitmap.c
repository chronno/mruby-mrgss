#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>
#include <raylib.h>

#include <mrgss.h>
#include <mrgss/bitmap.h>

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

static mrb_value mrgss_bitmap_initialize(mrb_state* mrb, mrb_value self) {
    mrb_value param, color;
    mrb_int args, height;
    char * filename;
    Color* cColor; 
    args = mrb_get_args(mrb, "o|io", &param, &height, &color);
    MR_Bitmap* image = mrb_malloc(mrb, sizeof(MR_Bitmap));
    switch (args) {
    case 1:
        filename = mrb_str_to_cstr(mrb, param);
        image->image = LoadImage(filename);
        image->name = filename;
        break;
    case 3:
        filename = "";
        cColor = DATA_PTR(color);
        image->image = GenImageColor(mrb_int(mrb, param), height, *cColor); 
    default:
        mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_NUMBER_ARGS);
        break;
    }
    printf("%s", image->name);
    DATA_PTR(self) = image;
    DATA_TYPE(self) = &bitmap_data_type;
    return self;
}


void mrgss_bitmap_init(mrb_state *mrb) {
    struct RClass* mrb_bitmap = mrgss_create_class(mrb, "Bitmap");
    mrb_define_method(mrb, mrb_bitmap, "initialize", mrgss_bitmap_initialize, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(2));
}