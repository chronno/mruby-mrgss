#include <mruby.h>
#include <raylib.h>
#ifndef MRUBY_MRGSS_FONT_H
#define MRUBY_MRGSS_FONT_H

typedef struct mrgss_font {
    Font font;
    char* name;
} MR_Font;

#endif