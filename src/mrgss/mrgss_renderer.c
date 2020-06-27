#include <stdlib.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/array.h>
#ifdef __EMSCRIPTEN__
#include <GLES2/gl2.h>
#include <GLES3/gl32.h>
#else
#include <gl3w.h>
#endif
#include <kazmath.h>
#include <mrgss.h>
#include <mrgss/renderer.h>


#define MAX_SPRITES 10000

const char* VertexShader = "#version 430 core\n"
"struct Args\n"
"{\n"          
    "mat4 params;\n"
    "mat4 modelView;\n"
"};\n"
"layout (location = 0 ) in vec2 position;\n"
"layout (location = 1 ) in vec2 texCoord;\n"
"layout (std430, binding=0) buffer shader_data {" 
    "Args args[];"
"};"
"uniform mat4 orthoView;" \
"out vec3 uv;\n"
"void main(void)\n"
"{\n"
    "gl_Position = orthoView * args[gl_VertexID / 4].modelView * vec4(position.x, position.y, 0.0, 1.0);\n"
    "uv = vec3(texCoord, args[gl_VertexID / 4].params[0][0]);\n"
"}\n";

const char* FragmentShader = "#version 430 core\n"
"out vec4 color;\n"
"in vec3 uv;\n"
"layout (binding=0) uniform sampler2DArray textures;\n"
//"uniform lowp float opacity;\n"
"void main(void)\n"
"{\n"
//"color = texture(textures, vec3(uv, 0));\n"
// "if(color.a <= 0.0){"
//      "discard;"
// "}"
//"color = texture(textures, vec3(uv.x, uv.y, uv.z));\n"
"color = vec4(1, 0, 0, 1);"
// "  color.a *= opacity;\n"
"}\n";

GLuint compile_shader(const char *shader, int type) {
    GLuint shaderid = glCreateShader(type);
    glShaderSource(shaderid, 1, &shader, NULL);
    glCompileShader(shaderid);
    return shaderid;
}


static GLuint compile_shader_program(GLuint vertexShader, GLuint fragmentShader) {
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram); //this is enabling the shader by default
    return shaderProgram;
}

#ifdef __EMSCRIPTEN__
static void loadDefaultShader(Renderer* renderer) {
    GLuint vId, fId;
    vId = compile_shader(VertexShader, GL_VERTEX_SHADER);
    fId = compile_shader(FragmentShader, GL_FRAGMENT_SHADER);
    renderer->sp = compile_shader_program(vId, fId);
    // should do something for emscripten as it wont work 
}
#else 
static void loadDefaultShader(Renderer* renderer) {
    GLuint vId, fId;
    vId = compile_shader(VertexShader, GL_VERTEX_SHADER);
    fId = compile_shader(FragmentShader, GL_FRAGMENT_SHADER);
    renderer->sp = compile_shader_program(vId, fId);
}
#endif

static void buildProjectionMatrix(Screen* screen) {
    kmMat4 ortho2D;
    kmMat4OrthographicProjection(&ortho2D, 0.0f, (float)screen->w, (float)screen->h, 0.0f, 0.0f, 1.0f);
    glUniformMatrix4fv(glGetUniformLocation(screen->renderer->sp, "orthoView"), 1, GL_FALSE, ortho2D.mat);
}

#ifdef __EMSCRIPTEN__
static void buildVertexBuffer(Renderer* renderer) {
    size_t bufferSize;
    glGenBuffers(1, &renderer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),  (GLvoid *) (sizeof (GL_FLOAT) * 2));
    bufferSize =  MAX_SPRITES * sizeof(Quad2D);
    renderer->vertexBuffer = malloc(sizeof(bufferSize));
    glBufferData(GL_ARRAY_BUFFER, bufferSize, renderer->vertexBuffer, GL_DYNAMIC_DRAW);
} 
#else 
static void buildVertexBuffer(Renderer* renderer) {
    size_t bufferSize;
    glGenBuffers(1, &renderer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),  (GLvoid *) (sizeof (GL_FLOAT) * 2));
    bufferSize =  MAX_SPRITES * sizeof(Quad2D);
    GLbitfield PBFlags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
    glBufferStorage(GL_ARRAY_BUFFER, bufferSize, 0, PBFlags);
    renderer->vertexBuffer = (Quad2D*)glMapBufferRange(GL_ARRAY_BUFFER, 0, bufferSize, PBFlags);
} 
#endif

#ifdef __EMSCRIPTEN__
static void buildShaderBuffer(Renderer* renderer) {
    // size_t bufferSize;
    // glGenBuffers(1, &renderer->sbo);
    // bufferSize =  MAX_SPRITES * sizeof(ShaderParams);
    // glBindBuffer(GL_SHADER_STORAGE_BUFFER, renderer->sbo);
    // renderer->shaderBuffer = malloc(sizeof(bufferSize));
    // glBufferData(GL_SHADER_STORAGE_BUFFER, bufferSize, renderer->shaderBuffer, GL_DYNAMIC_DRAW);
    // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, renderer->sbo);
}
#else 
static void buildShaderBuffer(Renderer* renderer) {
    size_t bufferSize;
    glGenBuffers(1, &renderer->sbo);
    bufferSize =  MAX_SPRITES * sizeof(ShaderParams);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, renderer->sbo);
    GLbitfield PBFlags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, bufferSize, 0, PBFlags);
    renderer->shaderBuffer = (ShaderParams*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, bufferSize, PBFlags);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, renderer->sbo);
}
#endif


void prepare_renderer() {
    Game* context = getContext();
    Screen* screen = getScreen();
    mrb_state* mrb = context->mrb;
    mrb_value rscreen = GET_IV_FROM(context->game, "@screen");
    mrb_value viewport = GET_IV_FROM(rscreen, "@viewport");
    mrb_value drawables = GET_IV_FROM(viewport, "#drawables");
    for (int i = 0; i < RARRAY_LEN(drawables); i++) {
        mrb_value rsprite = mrb_ary_entry(drawables, i);
        Sprite* sprite = DATA_PTR(rsprite);
    //     //rbitmap = MRG_GET_PROP_FROM(rsprite, "@bitmap");
    //     //screen->renderer->persistentShaderBuffer[sprite->index].params[0] = (float)register_bitmap(renderer, DATA_PTR(rbitmap));
        sync_sprite_position(&(screen->renderer->vertexBuffer[i]), sprite);
        sync_sprite_transforms(&screen->renderer->shaderBuffer[i], sprite);
    //     //renderer->persistentShaderBuffer[i].params[1] = 0;
    }
    #ifdef __EMSCRIPTEN__
    glBindBuffer(GL_ARRAY_BUFFER, screen->renderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, MAX_SPRITES * sizeof(Quad2D), screen->renderer->vertexBuffer, GL_DYNAMIC_DRAW);
    // glBindBuffer(GL_SHADER_STORAGE_BUFFER, screen->renderer->sbo);
    // glBufferData(GL_SHADER_STORAGE_BUFFER, MAX_SPRITES * sizeof(ShaderParams), screen->renderer->shaderBuffer, GL_DYNAMIC_DRAW);
    #endif
    glDrawArrays(GL_QUADS, 0, RARRAY_LEN(drawables) * 4);
}


void initialize_renderer() {
    Screen* screen = getScreen();
    screen->renderer = malloc(sizeof(Renderer));
    loadDefaultShader(screen->renderer);
    buildProjectionMatrix(screen);
    buildVertexBuffer(screen->renderer);
    buildShaderBuffer(screen->renderer);
    //buildTexBuffer(screen->renderer);
}