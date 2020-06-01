#include <stdio.h>
#include <mrgss.h>

void sync_sprite_position(mrb_state* mrb, mrb_value sprite) {
    Sprite* csprite = DATA_PTR(sprite);
    //Top Left corner
    csprite->vertexData.vertices[0].x = (GLfloat)csprite->position->x;
    csprite->vertexData.vertices[0].y = (GLfloat)csprite->position->y;

    csprite->vertexData.vertices[0].u = ((GLfloat)csprite->src_rect->x) / (float)MAX_IMG_SIZE;
    csprite->vertexData.vertices[0].v = ((GLfloat)csprite->src_rect->y) / (float)MAX_IMG_SIZE;
    //Top right corner
    csprite->vertexData.vertices[1].x = ((GLfloat)csprite->position->x) + ((GLfloat)csprite->src_rect->w);
    csprite->vertexData.vertices[1].y = (GLfloat)csprite->position->y;

    csprite->vertexData.vertices[1].u = (((GLfloat)csprite->src_rect->x) + ((GLfloat)csprite->src_rect->w)) / (float)MAX_IMG_SIZE;
    csprite->vertexData.vertices[1].v = ((GLfloat)csprite->src_rect->y) / (float)MAX_IMG_SIZE;
    //bottom left corner
    csprite->vertexData.vertices[2].x = ((GLfloat)csprite->position->x) + ((GLfloat)csprite->src_rect->w);
    csprite->vertexData.vertices[2].y = ((GLfloat)csprite->position->y) + ((GLfloat)csprite->src_rect->h);
    
    csprite->vertexData.vertices[2].u = (((GLfloat)csprite->src_rect->x) + ((GLfloat)csprite->src_rect->w)) / (float)MAX_IMG_SIZE;
    csprite->vertexData.vertices[2].v = (((GLfloat)csprite->src_rect->y) + ((GLfloat)csprite->src_rect->h)) / (float)MAX_IMG_SIZE;
    //bottom right
    csprite->vertexData.vertices[3].x = ((GLfloat)csprite->position->x);
    csprite->vertexData.vertices[3].y = ((GLfloat)csprite->position->y) + ((GLfloat)csprite->src_rect->h);

    csprite->vertexData.vertices[3].u = ((GLfloat)csprite->src_rect->x) / (float)MAX_IMG_SIZE;
    csprite->vertexData.vertices[3].v = (((GLfloat)csprite->src_rect->y) + ((GLfloat)csprite->src_rect->h)) / (float)MAX_IMG_SIZE;
    csprite->dirty = TRUE;
}

void sync_sprite_transforms(Sprite *sprite){
    kmMat4 buffer;
    kmMat4 transforms;
    if (sprite->angle >= 360 || sprite->angle < -360) {
        sprite->angle = (float) fmod(sprite->angle, 360);
    }
    if (sprite->angle < 0) {
	    sprite->angle += 360;
    }
    
    kmMat4Identity(&buffer);
    kmMat4Translation(&transforms, (float)(-sprite->position->x - sprite->origin->x), (float)(-sprite->position->y - sprite->origin->y), 0.0);
    kmMat4RotationZ(&buffer, sprite->angle * 3.141592654f / 180.0f); 
    kmMat4Multiply(&transforms,&buffer, &transforms); 
    kmMat4Translation(&buffer, (float)(sprite->position->x + sprite->origin->x), (float)(sprite->position->y + sprite->origin->y), 0.0);
    kmMat4Multiply(&transforms,&buffer, &transforms);
    memcpy(sprite->shaderParams.transforms, transforms.mat, sizeof(GLfloat) * 16 );
    sprite->dirty = TRUE;
}