#include <mrgss.h>

struct mrb_data_type const sprite_data_type = {"MRGSS::Sprite", mrb_free};

static void add_as_dirty(mrb_state* mrb, mrb_value self) {
    mrb_value viewport;
    mrb_value dirty;
    Sprite* sprite;
    GameRenderer* renderer;
    sprite = DATA_PTR(self);
    if (sprite->marked) { return; }
    viewport = MRG_GET_PROP("@viewport");
    dirty = MRG_GET_PROP_FROM(viewport, "@dirty_drawables");
    renderer = DATA_PTR(viewport);
    renderer->dirty = TRUE;
    mrb_ary_push(mrb, dirty, self);
    sprite->marked = TRUE;
}

static void register_sprite(mrb_state* mrb, mrb_value self) {
    Sprite *sprite;
    GameRenderer *renderer;
    mrb_value index;
    mrb_value drawables;
    mrb_value viewport = MRG_GET_PROP("@viewport");
    drawables = MRG_GET_PROP_FROM(viewport, "@drawables");
    renderer = DATA_PTR(viewport);
    sprite = DATA_PTR(self);
    if(renderer->freeSpots > 0) {
        index = mrb_funcall(mrb, drawables, "find_index", 1, mrb_nil_value());
        sprite->index = mrb_int(mrb, index);
        mrb_ary_set(mrb, drawables, mrb_int(mrb, index), mrb_nil_value());
        renderer->freeSpots -= 1;
    } else {
        sprite->index = RARRAY_LEN(MRG_GET_PROP_FROM(viewport, "@drawables"));
        mrb_ary_push(mrb, MRG_GET_PROP_FROM(viewport, "@drawables"), self);
    }    
}

static mrb_value initialize(mrb_state* mrb, mrb_value self) {
    mrb_value viewport;
    Sprite* sprite;
    mrb_get_args(mrb, "o", &viewport);
    if ( mrgss_obj_is_a(mrb, viewport, "Viewport") ) {
        sprite = mrb_malloc(mrb, sizeof(Sprite));
        sprite->position = mrb_malloc(mrb, sizeof(Point));
        sprite->origin = mrb_malloc(mrb, sizeof(Point));
        sprite->zoom = mrb_malloc(mrb, sizeof(Point));
        sprite->src_rect = mrb_malloc(mrb, sizeof(Rect));
        sprite->position->x = 0;
        sprite->position->y = 0;
        sprite->src_rect->x = 0;
        sprite->src_rect->y = 0;
        sprite->src_rect->w = 0;
        sprite->src_rect->h = 0;
        sprite->origin->x = 0;
        sprite->origin->y = 0;
        sprite->zoom->x = 1;
        sprite->zoom->y = 1;
        sprite->angle = 0;
        sprite->dirtyPosition = GL_FALSE;
        sprite->dirtyTransforms = GL_FALSE;
        sprite->marked = GL_FALSE;
        MRG_SET_PROP("@viewport", viewport);
        DATA_PTR(self) = sprite;
        DATA_TYPE(self) = &sprite_data_type;
        register_sprite(mrb, self);
        return self;
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "viewport expected");
    }
}


mrb_value set_bitmap(mrb_state* mrb, mrb_value self) {
    mrb_value value;
    Bitmap* bmp;
    Sprite* spr;
    mrb_get_args(mrb, "o", &value);
    if (mrgss_obj_is_a(mrb, value, "Bitmap")) {
        bmp = DATA_PTR(value);
        spr = DATA_PTR(self);
        spr->src_rect->w = bmp->width;
        spr->src_rect->h = bmp->height;
        spr->dirtyPosition = TRUE;
        spr->dirtyTransforms = TRUE;
        MRG_SET_PROP("@bitmap", value);
        add_as_dirty(mrb, self);
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "wanted a Bitmap");
    }
    return mrb_nil_value();
}

mrb_value get_bitmap(mrb_state* mrb, mrb_value self) {
    return MRG_GET_PROP("@bitmap");
}


mrb_value set_rect(mrb_state* mrb, mrb_value self) {
    mrb_value value;
    Sprite* sprite;
    Rect* rect;
    mrb_get_args(mrb, "o", &value);
    if (mrgss_obj_is_a(mrb, value, "Rect")) {
        sprite = DATA_PTR(self);
        rect = DATA_PTR(value);
        sprite->src_rect = rect;    
        sprite->dirtyPosition = TRUE;
        sprite->dirtyTransforms = TRUE;
        MRG_SET_PROP("@src_rect", value);
        add_as_dirty(mrb, self);
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "wanted a Rect");
    }
    return mrb_nil_value();
}

mrb_value get_rect(mrb_state* mrb, mrb_value self) {
    return MRG_GET_PROP("@src_rect");
}

mrb_value set_x(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Sprite* sprite = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    sprite->position->x = value;
    sprite->dirtyPosition = TRUE;
    sprite->dirtyTransforms = TRUE;
    add_as_dirty(mrb, self);
    return self;
}

mrb_value get_x(mrb_state* mrb, mrb_value self) {
    Sprite* sprite = DATA_PTR(self);
    return mrb_fixnum_value(sprite->position->x);
}

mrb_value set_y(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Sprite* sprite = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    sprite->position->y = value;
    sprite->dirtyPosition = TRUE;
    sprite->dirtyTransforms = TRUE;
    add_as_dirty(mrb, self);
    return self;
}

mrb_value get_y(mrb_state* mrb, mrb_value self) {
    Sprite* sprite = DATA_PTR(self);
    return mrb_fixnum_value(sprite->position->y);
}

mrb_value get_angle(mrb_state* mrb, mrb_value self) {
    Sprite* sprite = DATA_PTR(self);
    return mrb_fixnum_value(sprite->angle);
}

mrb_value set_angle(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Sprite* sprite = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    sprite->angle = value;
    sprite->dirtyTransforms = TRUE;
    add_as_dirty(mrb, self);
    return self;
}

mrb_value set_ox(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Sprite* sprite = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    sprite->origin->x = value;
    sprite->dirtyTransforms = TRUE;
    add_as_dirty(mrb, self);
    return self;
}

mrb_value get_ox(mrb_state* mrb, mrb_value self) {
    Sprite* sprite = DATA_PTR(self);
    return mrb_fixnum_value(sprite->origin->x);
}

mrb_value set_oy(mrb_state* mrb, mrb_value self) {
    mrb_int value;
    Sprite* sprite = DATA_PTR(self);
    mrb_get_args(mrb, "i", &value);
    sprite->origin->y = value;
    sprite->dirtyTransforms = TRUE;
    add_as_dirty(mrb, self);
    return self;
}

mrb_value get_oy(mrb_state* mrb, mrb_value self) {
    Sprite* sprite = DATA_PTR(self);
    return mrb_fixnum_value(sprite->origin->y);
}

mrb_value dispose(mrb_state* mrb, mrb_value self) {
    mrb_value viewport, drawables;
    GameRenderer* renderer;
    Sprite* sprite = DATA_PTR(self);
    viewport = MRG_GET_PROP("@viewport");
    drawables = MRG_GET_PROP_FROM(viewport, "@drawables");
    renderer = DATA_PTR(viewport);
    renderer->freeSpots += 1;
    mrb_ary_set(mrb, drawables, sprite->index, mrb_nil_value());
    mrb_free(mrb, sprite);
    return mrb_true_value();
}


void create_sprite_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Sprite");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "bitmap=", set_bitmap, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "bitmap", get_bitmap, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "src_rect=", set_rect, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "src_rect", get_rect, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "x=", set_x, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "x", get_x, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "y=", set_y, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "y", get_y, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "angle=", set_angle, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "angle", get_angle, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "origin_x=", set_ox, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "origin_x", get_ox, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "origin_y=", set_oy, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "origin_y", set_oy, MRB_ARGS_NONE());
    mrb_define_method(mrb, type, "dispose", dispose, MRB_ARGS_NONE());
}