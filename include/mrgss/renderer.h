#ifndef MRUBY_MRGSS_RENDERER_H
#define MRUBY_MRGSS_RENDERER_H

#ifdef __EMSCRIPTEN__
#include <GLES2/gl2.h>
#include <GLES3/gl32.h>
#else
#include <gl3w.h>
#endif

typedef struct mrgss_vertex2d {
    GLfloat x, y; //vertex position
    GLfloat u, v; //textures position
} Vertex2D;

typedef struct mrgss_quad {
    Vertex2D vertices[4];
} Quad2D;

typedef struct mrgss_shader {
    GLfloat params[16];
    GLfloat transforms[16];
} ShaderParams;

typedef struct mrgss_renderer {
    GLuint vbo;
    GLuint sp;
    GLuint sbo;
    Quad2D* vertexBuffer;
    ShaderParams* shaderBuffer;
    
} Renderer;


void initialize_renderer();
void prepare_renderer();
#endif