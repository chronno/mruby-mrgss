#ifndef MRUBY_MRGSS_TYPES_H
#define MRUBY_MRGSS_TYPES_H
#include <mrgss.h>


typedef struct mrgss_vertex {
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
    GLuint txc; // this is a counter that will tell me how many textures i have stored in the array and assign a depth value to the bitmap object
    GLuint spp; // this is the id of the default shader program should be usefull to fill in uniforms
    GLint glMajor;
    GLint glMinor;
    Quad2D* persistentVertexBuffer; // this should work as a Vertex2D array that will be streamming to the videoboard 
} GameRenderer;

typedef struct mrgss_context {
    mrb_state *mrb;
    mrb_value game, batch;
    GLFWwindow* window;
    GameRenderer* renderer;
} GameContext;

typedef struct mrgss_rect { 
    mrb_int x, y, w, h; 
} Rect;

typedef struct mrgss_point {
    mrb_int x, y; 
} Point;

typedef struct mrgss_color {
    mrb_int r, g, b, a; 
} Color;

typedef struct mrgss_bitmap {
    mrb_int width, height, format, layer;
    unsigned char* data;
} Bitmap;

typedef struct mrgss_sprite {
    Quad2D vertexData;
    GLfloat x, y; //position
    GLfloat rx, ry, rw, rh; //src rect
    GLboolean dirty; // should be used to know when to redraw
} Sprite;



#endif