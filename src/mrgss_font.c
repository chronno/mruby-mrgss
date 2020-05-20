#include <stdlib.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>

#include <raylib.h>

#include <mrgss.h>
#include <mrgss/font.h>

#define MRGSS_MODULE mrb_module_get(mrb, "MRGSS")

static void mrgss_font_free(mrb_state *mrb, void *p) {
    if (p) {       
        MR_Font* font = (MR_Font*) p;
        UnloadFont(font->font);
        mrb_free(mrb, p);
    }
}

static const struct mrb_data_type font_data_type = {
  "MRGSS::Font", mrgss_font_free
};

static mrb_value mrgss_font_initialize(mrb_state* mrb, mrb_value self) {
    mrb_int args;
    char* font_name;    
    MR_Font* font;
    args = mrb_get_args(mrb, "|z", &font_name);
    font = mrb_malloc(mrb, sizeof(MR_Font));    
    switch (args) {
    case 0:
        font->font = GetFontDefault();
        font->name = "default";
        break;
    case 1:
        font->font= LoadFont(font_name);
        font->name = font_name;
        break;
    default:
        mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_NUMBER_ARGS);
    }
    DATA_PTR(self) = font;
    DATA_TYPE(self) = &font_data_type;
    return self;
}

mrb_value mrgss_font_draw(mrb_state* mrb, mrb_value self) {
    char* text;
    mrb_value rect, color;
    Rectangle* cRect;
    Color* cColor;
    MR_Font* font = DATA_PTR(self);
    mrb_float size, spacing;
    mrb_bool wrap;
    mrb_get_args(mrb, "zoffbo", &text, &rect, &size, &spacing, &wrap, &color);
    if (mrgss_obj_is_a(mrb, rect, "Rectangle") && mrgss_obj_is_a(mrb, color, "Color")) {
        cRect = DATA_PTR(rect);
        cColor = DATA_PTR(color);
        DrawTextRec(font->font, text, *cRect, size, spacing, wrap, *cColor);
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, WRONG_TYPE_ARGS);
    }
    return mrb_nil_value();
}   

void mrgss_font_init(mrb_state *mrb) {
    struct RClass* mrb_font = mrgss_create_class(mrb, "Font");
    mrb_define_method(mrb, mrb_font, "initialize", mrgss_font_initialize, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, mrb_font, "draw_text", mrgss_font_draw, MRB_ARGS_REQ(6));
}