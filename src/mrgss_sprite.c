#include <stdio.h>
#include <mrgss.h>

void sync_sprite_position(Quad2D* quad, Sprite* sprite) {
    //Top Left corner
    quad->vertices[0].x = (GLfloat)sprite->position->x;
    quad->vertices[0].y = (GLfloat)sprite->position->y;
    quad->vertices[0].u = ((GLfloat)sprite->src_rect->x) / (float)MAX_IMG_SIZE;
    quad->vertices[0].v = ((GLfloat)sprite->src_rect->y) / (float)MAX_IMG_SIZE;
    
    //Top right corner
    quad->vertices[1].x = ((GLfloat)sprite->position->x) + ((GLfloat)sprite->src_rect->w);
    quad->vertices[1].y = (GLfloat)sprite->position->y;

    quad->vertices[1].u = (((GLfloat)sprite->src_rect->x) + ((GLfloat)sprite->src_rect->w)) / (float)MAX_IMG_SIZE;
    quad->vertices[1].v = ((GLfloat)sprite->src_rect->y) / (float)MAX_IMG_SIZE;
    //bottom left corner
    quad->vertices[2].x = ((GLfloat)sprite->position->x) + ((GLfloat)sprite->src_rect->w);
    quad->vertices[2].y = ((GLfloat)sprite->position->y) + ((GLfloat)sprite->src_rect->h);
    
    quad->vertices[2].u = (((GLfloat)sprite->src_rect->x) + ((GLfloat)sprite->src_rect->w)) / (float)MAX_IMG_SIZE;
    quad->vertices[2].v = (((GLfloat)sprite->src_rect->y) + ((GLfloat)sprite->src_rect->h)) / (float)MAX_IMG_SIZE;
    //bottom right
    quad->vertices[3].x = ((GLfloat)sprite->position->x);
    quad->vertices[3].y = ((GLfloat)sprite->position->y) + ((GLfloat)sprite->src_rect->h);

    quad->vertices[3].u = ((GLfloat)sprite->src_rect->x) / (float)MAX_IMG_SIZE;
    quad->vertices[3].v = (((GLfloat)sprite->src_rect->y) + ((GLfloat)sprite->src_rect->h)) / (float)MAX_IMG_SIZE;
}

void sync_sprite_transforms(ShaderParams* shader, Sprite *sprite) {
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
    memcpy(shader->transforms, transforms.mat, sizeof(GLfloat) * 16 );
}