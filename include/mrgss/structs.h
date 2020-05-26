#ifndef MRUBY_MRGSS_TYPES_H
#define MRUBY_MRGSS_TYPES_H
#include <mruby.h>
#include <raylib.h>

/*
 * Base Structures
*/ 
typedef struct mrgss_rectangle {
    mrb_int x, y, w, h;
} MR_Rect;

typedef struct mrgss_color {
    mrb_int r, g, b, a;
} MR_Color;

typedef struct mrgss_point {
    mrb_int x, y;
} MR_Point;

typedef struct mrgss_screen {
    void *window;
    mrb_bool fullscreen, disposed;
    mrb_int width, height;
    char *title;
} MR_Screen;

typedef struct mrgss_bitmap {
    const char* name;
    Image image;
} MR_Bitmap;

typedef struct mrgss_sprite {
    MR_Bitmap* bitmap;
    Texture texture;
    MR_Rect srcRect, dstRect;
    mrb_float angle;
} MR_Sprite;
/*
 * Usefull 
*/
typedef struct mrgss_context {
    mrb_state *mrb;
    MR_Screen *screen;
    mrb_value game;
} MR_Context;
#endif