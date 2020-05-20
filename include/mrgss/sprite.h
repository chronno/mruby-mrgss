#include <mruby.h>
#include <raylib.h>
#include <mrgss/bitmap.h>
#ifndef MRUBY_MRGSS_SPRITE_H
#define MRUBY_MRGSS_SPRITE_H


typedef struct mrgss_sprite {
    MR_Bitmap* bitmap;
    Texture texture;
    Rectangle srcRect, dstRect;
    mrb_float angle;
} MR_Sprite;

#endif