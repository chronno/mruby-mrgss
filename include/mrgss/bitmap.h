#include <mruby.h>
#include <raylib.h>

#ifndef MRUBY_MRGSS_BITMAP_H
#define MRUBY_MRGSS_BITMAP_H

typedef struct mrgss_bitmap {
    char* name;
    Image image;
} MR_Bitmap;

#endif