#include <mruby.h>
#include <mruby/data.h>
#include <mrgss/gl.h>
#include <mrgss/structs.h>
#include <mrgss/utils.h>

void sync_sprite(mrb_state* mrb, mrb_value sprite) {
    Sprite* csprite = DATA_PTR(sprite);
    
    csprite->vertexData.vertices[0].x = csprite->x;
    csprite->vertexData.vertices[0].y = csprite->y;
    csprite->vertexData.vertices[0].u = csprite->rx / (float)MAX_IMG_SIZE;
    csprite->vertexData.vertices[0].v = csprite->ry / (float)MAX_IMG_SIZE;
    //Top right corner
    csprite->vertexData.vertices[1].x = csprite->x + csprite->rw;
    csprite->vertexData.vertices[1].y = csprite->y;
    csprite->vertexData.vertices[1].u = (csprite->rx + csprite->rw) / (float)MAX_IMG_SIZE;
    csprite->vertexData.vertices[1].v = csprite->ry / (float)MAX_IMG_SIZE;
    //bottom left corner
    csprite->vertexData.vertices[2].x = csprite->x + csprite->rw;
    csprite->vertexData.vertices[2].y = csprite->y + csprite->rh;
    csprite->vertexData.vertices[2].u = (csprite->rx + csprite->rw) / (float)MAX_IMG_SIZE;
    csprite->vertexData.vertices[2].v = (csprite->ry + csprite->rh) / (float)MAX_IMG_SIZE;
    //bottom right
    csprite->vertexData.vertices[3].x = csprite->x;
    csprite->vertexData.vertices[3].y = csprite->y + csprite->rh;
    csprite->vertexData.vertices[3].u = csprite->rx / (float)MAX_IMG_SIZE;
    csprite->vertexData.vertices[3].v = (csprite->ry + csprite->rh) / (float)MAX_IMG_SIZE;
    csprite->dirty = GL_TRUE;
}