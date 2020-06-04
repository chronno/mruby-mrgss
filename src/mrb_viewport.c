#include <mrgss.h>

static const struct mrb_data_type viewport_data_type = {
  "MRGSS::Viewport", mrb_free
};

static mrb_value initialize(mrb_state *mrb, mrb_value self) {
    GameRenderer* renderer;
    mrb_int width, height;
    mrb_get_args(mrb, "ii", &width, &height);
    renderer = mrb_malloc(mrb, sizeof(GameRenderer));
    renderer->width = width;
    renderer->height = height;
    MRG_SET_PROP("@drawables", mrb_ary_new(mrb));
    MRG_SET_PROP("@dirty_drawables", mrb_ary_new(mrb));
    initialize_renderer(renderer);
    DATA_PTR(self) = renderer;
    DATA_TYPE(self) = &viewport_data_type;
    return self;
}



void create_viewport_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Viewport");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(2));
}