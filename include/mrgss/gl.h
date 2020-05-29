#ifndef MRUBY_MRGSS_GL_H
#define MRUBY_MRGSS_GL_H
#ifndef __EMSCRIPTEN__
#include <GL/gl3w.h>
#else 
#include <GL/Regal.h>
#endif
#include <mrgss/structs.h>

#define MAX_SPRITES 10000000
#define MAX_IMG_SIZE 4000
#define TEX_LAYERS 200

extern const char* VertexShader;
extern const char* FragmentShader;
GLuint compile_shader(const char *shader, int type);
GLuint compile_shader_program(GLuint vertexShader, GLuint fragmentShader);
void bitmap_from_file(Bitmap* bmp, char* filename);
#endif

