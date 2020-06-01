#include <mrgss.h>

static GLbitfield PBFlags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;

static void buildVertexBuffer(GameRenderer* renderer) {
    size_t bufferSize;
    glGenBuffers(1, &renderer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),  (GLvoid *) (sizeof (GL_FLOAT) * 2));
    bufferSize =  MAX_SPRITES * sizeof(Quad2D);
    if (renderer->glMajor >= 4 && renderer->glMinor >= 4)  {
        glBufferStorage(GL_ARRAY_BUFFER, bufferSize, 0, PBFlags);
        renderer->persistentVertexBuffer = (Quad2D*)glMapBufferRange(GL_ARRAY_BUFFER, 0, bufferSize, PBFlags);
    } else {
        renderer->persistentVertexBuffer = malloc(sizeof(bufferSize));
    }
}

static void buildShaderParamsBuffer(GameRenderer* renderer) {
    size_t bufferSize;
    glGenBuffers(1, &renderer->ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, renderer->ssbo);
    bufferSize =  MAX_SPRITES * sizeof(ShaderParams);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, bufferSize, 0, PBFlags);
    renderer->persistentShaderBuffer = (ShaderParams*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, bufferSize, PBFlags);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, renderer->ssbo);
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
    context->renderer->txc = 0;
    loadDefaultShader(context->renderer); //loads and enables default shader shall i let other users to modify this?
    buildVertexBuffer(context->renderer); //this should enable data transfer between the renderer persistent vertex buffer and the video board
    buildShaderParamsBuffer(context->renderer); //this should enable several params to the shader
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

GLsync gSync;

void mrgss_renderer_lock_gl_buffer() {
    if( gSync ) {
        glDeleteSync( gSync );	
    }
    gSync = glFenceSync( GL_SYNC_GPU_COMMANDS_COMPLETE, 0 );
}

void mrgss_renderer_wait_for_gl_lock() {
    if( gSync ) {
        while( 1 ) {
            GLenum waitReturn = glClientWaitSync( gSync, GL_SYNC_FLUSH_COMMANDS_BIT, 1 );
            if (waitReturn == GL_ALREADY_SIGNALED || waitReturn == GL_CONDITION_SATISFIED) {
              return;
            }
        }
    }
}

int prepare_renderer(GameContext* context, mrb_value batch) {
    int counter;
    mrb_value drawables;
    mrb_value rsprite, rbitmap;
    Sprite *sprite;
    mrb_state* mrb = context->mrb;
    counter = 0;
    drawables = MRG_GET_PROP_FROM(batch, "@drawables");
    /////check if renderer needs sorting
    counter = RARRAY_LEN(drawables);
    mrgss_renderer_wait_for_gl_lock();
    for(int i = 0; i < RARRAY_LEN(drawables); i++) {/////check if renderer is in sync with sprites to draw
        rsprite = mrb_ary_entry(drawables, i);
        sprite = DATA_PTR(rsprite);
        if(sprite->dirty) {
            rbitmap = MRG_GET_PROP_FROM(rsprite, "@bitmap");
            context->renderer->persistentShaderBuffer[i].params[0] = (float)register_bitmap(context, DATA_PTR(rbitmap));
            context->renderer->persistentShaderBuffer[i].params[1] = 0;           
            memcpy(&(context->renderer->persistentShaderBuffer[i].transforms), &(sprite->shaderParams.transforms), sizeof(GLfloat) * 16); 
            context->renderer->persistentVertexBuffer[i] = sprite->vertexData;
            sprite->dirty = FALSE;
            // printf("%i :[%f, %f][%f, %f][%f, %f][%f, %f]\n", i,
            //     context->renderer->persistentVertexBuffer[i].vertices[0].x,
            //     context->renderer->persistentVertexBuffer[i].vertices[0].y,
            //     context->renderer->persistentVertexBuffer[i].vertices[1].x,
            //     context->renderer->persistentVertexBuffer[i].vertices[1].y,
            //     context->renderer->persistentVertexBuffer[i].vertices[2].x,
            //     context->renderer->persistentVertexBuffer[i].vertices[2].y,
            //     context->renderer->persistentVertexBuffer[i].vertices[3].x,
            //     context->renderer->persistentVertexBuffer[i].vertices[3].y
            //     );
        }
        //memcpy(&(renderer->persistentShaderBuffer[i]), &sprite->transforms, sizeof(sprite->transforms)); 
    }
    
    return counter;
}



void renderer_draw(GameContext* context, int renderables) {
    glDrawArrays(GL_QUADS, 0, renderables * 4);
    mrgss_renderer_lock_gl_buffer(); 
    printOglError("render");
}