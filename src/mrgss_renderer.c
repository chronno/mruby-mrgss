#include <stdlib.h>
#include <string.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/array.h>
#ifndef __EMSCRIPTEN__
#include <GL/gl3w.h>
#else 
#include <GL/Regal.h>
#endif
#include <GLFW/glfw3.h>
#include <mrgss.h>
#include <mrgss/utils.h>
#include <mrgss/structs.h>
#include <mrgss/gl.h>
#include <kazmath.h>


static GLbitfield PBFlags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;

static void buildPersistentVertexBuffer(GameRenderer* renderer) {
    size_t bufferSize;
    glGenBuffers(1, &renderer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),  (GLvoid *) (sizeof (GL_FLOAT) * 2));
    bufferSize =  MAX_SPRITES * sizeof(Quad2D);
    glBufferStorage(GL_ARRAY_BUFFER, bufferSize, 0, PBFlags);
    renderer->persistentVertexBuffer = (Quad2D*)glMapBufferRange(GL_ARRAY_BUFFER, 0, bufferSize, PBFlags);
}

static void buildTexturesBuffer(GameRenderer* renderer) {
    glGenTextures(1, &renderer->tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, renderer->tex);
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, MAX_IMG_SIZE, MAX_IMG_SIZE, TEX_LAYERS);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
}

static void buildProjectionMatrix(GameContext *context) {
    kmMat4 ortho2D;
    GLint width, height;
    glfwGetWindowSize(context->window, &width, &height);
    kmMat4OrthographicProjection(&ortho2D, 0.0f, width, height, 0.0f, 0.0f, 1.0f);
    glUniformMatrix4fv(glGetUniformLocation(context->renderer->spp, "orthoView"), 1, GL_FALSE, ortho2D.mat);
}

static void loadDefaultShader(GameRenderer* renderer) {
    GLuint vId, fId;
    vId = compile_shader(VertexShader, GL_VERTEX_SHADER);
    fId = compile_shader(FragmentShader, GL_FRAGMENT_SHADER);
    renderer->spp = compile_shader_program(vId, fId);
}

void initialize_renderer(GameContext* context) {
    loadDefaultShader(context->renderer); //loads and enables default shader shall i let other users to modify this?
    buildPersistentVertexBuffer(context->renderer); //this should enable data transfer between the renderer persistent vertex buffer and the video board
    buildTexturesBuffer(context->renderer); //this should reduce texture transfers and state switching while drawing a batch
    buildProjectionMatrix(context); // we should use orthographic projection always in order to render 2d 
}

int printOglError(const char *method) {
    GLenum glErr;
    int retCode = 0;
    glErr = glGetError();
    if (glErr != GL_NO_ERROR) {
        printf("glError in method %s : %i\n", method, glErr);
        retCode = 1;
    }
    return retCode;
}

void renderer_draw(GameContext* context) {
    mrb_state* mrb = context->mrb;
    mrb_value rdrawables = MRG_GET_PROP_FROM(context->game, "drawables");
    /////check if renderer needs sorting
    for(int i = 0; i < RARRAY_LEN(rdrawables); i++) {/////check if renderer is in sync with sprites to draw
        mrb_value rsprite = mrb_ary_entry(rdrawables, i);
        Sprite *sprite = DATA_PTR(rsprite);
        context->renderer->persistentVertexBuffer[i] = sprite->vertexData;
        //memcpy(&(renderer->persistentShaderBuffer[i]), &sprite->transforms, sizeof(sprite->transforms)); 
    }
    glDrawArrays(GL_QUADS, 0, RARRAY_LEN(rdrawables) * 4);
    printOglError("render");
}


void register_sprite(GameContext* context, mrb_value sprite) {
    
}