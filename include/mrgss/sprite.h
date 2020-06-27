#ifndef MRUBY_MRGSS_SPRITE_H
#define MRUBY_MRGSS_SPRITE_H
#include <mruby.h>
#include <mrgss.h>
/* Create MRuby type */
void create_sprite_type(mrb_state* mrb);

typedef struct mrgss_sprite {
    Point* zoom;
    Point* position;
    Point* origin;
    mrb_int angle;
    Rect* src_rect;
} Sprite;


Sprite* initialize_sprite(mrb_state* mrb);
void sync_sprite_position(Quad2D* quad, Sprite* sprite);
void sync_sprite_transforms(ShaderParams* shader, Sprite *sprite);
#endif