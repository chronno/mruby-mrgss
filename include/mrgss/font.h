#include <mruby.h>
#include <raylib.h>

typedef struct mrgss_font {
    Font font;
    char* name;
} MR_Font;