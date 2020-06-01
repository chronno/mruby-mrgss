#ifndef MRUBY_MRGSS_GL_H
#define MRUBY_MRGSS_GL_H
#include <mrgss.h>
#include <mrgss/types.h>
#define MAX_SPRITES 1000000
#define MAX_IMG_SIZE 4000
#define TEX_LAYERS 100

extern const char* VertexShader;
extern const char* FragmentShader;


GLuint compile_shader(const char *shader, int type);
GLuint compile_shader_program(GLuint vertexShader, GLuint fragmentShader);
void bitmap_from_file(Bitmap* bmp, char* filename);
int register_bitmap(GameContext* context, Bitmap* bitmap);


#endif

