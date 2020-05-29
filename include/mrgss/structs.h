#ifndef MRUBY_MRGSS_STRUCTS_H
#define MRUBY_MRGSS_STRUCTS_H
#include <mruby.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#include <gl/gl3w.h>
#endif
#include <GLFW/glfw3.h>
#include <vendor/stretchy_buffer.h>

typedef struct mrgss_vertext {
    GLfloat x, y; //vertex position
    GLfloat u, v; //textures position
} Vertex2D;


typedef struct mrgss_quad {
    Vertex2D vertices[4]; // un rectangulo que es lo que requiero para dibujar cualquier imagen tiene 4 vertices la idea es poder apuntar facilmente en el persistent vertex buffer
} Quad2D;

typedef struct mrgss_renderer {
    GLuint vao; //vertex array object pointer
    GLuint vbo; //vertex buffer object pointer
    GLuint tex; //this is a texture 2d array pointer gonna be used to store as much textures as posible in order to avoid texture switching 
    GLuint spp; // this is the id of the default shader program should be usefull to fill in uniforms
    Quad2D* persistentVertexBuffer; // this should work as a Vertex2D array that will be streamming to the videoboard 
} GameRenderer;

typedef struct mrgss_context {
    mrb_state *mrb;
    mrb_value game;
    GLFWwindow* window;
    GameRenderer* renderer;
} GameContext;

typedef struct mrgss_bitmap {
    int width, height, format, layer;
    unsigned char* data;
} Bitmap;

typedef struct mrgss_sprite {
    Quad2D vertexData;
    GLfloat x, y, rx, ry, rw, rh;
} Sprite;

#endif