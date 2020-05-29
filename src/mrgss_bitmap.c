#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb_mage.h>


void from_file(char* filename) {
    int width, height, format;
    stbi_load(filename, &width, &height, &format, STBI_rgb_alpha);
}