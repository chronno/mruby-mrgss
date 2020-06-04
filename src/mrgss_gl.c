#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb_mage.h>
#include <mrgss.h>

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
"color = texture(textures, vec3(uv.x, uv.y, uv.z));\n"
//"color = vec4(uv.x, uv.y, uv.x, uv.y);"
// "  color.a *= opacity;\n"
"}\n";


static void shader_log(GLuint shaderId){
    GLint bufflen;
    GLchar* log;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &bufflen);
    log = malloc(sizeof (GLchar) * bufflen);
    glGetShaderInfoLog(shaderId, bufflen, 0, log);
    printf("shader compiling log: %s\n", log);
    free(log);
}

static void shader_program_log(GLuint shaderId){
    GLint bufflen;
    GLchar* log;
    glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &bufflen);
    log = malloc(sizeof (GLchar) * bufflen);
    glGetProgramInfoLog(shaderId, bufflen, 0, log);
    printf("shader program linking log: %s\n", log);
    free(log);
}

GLuint compile_shader(const char *shader, int type) {
    GLuint shaderid = glCreateShader(type);
    glShaderSource(shaderid, 1, &shader, NULL);
    glCompileShader(shaderid);
    shader_log(shaderid);
    return shaderid;
}

GLuint compile_shader_program(GLuint vertexShader, GLuint fragmentShader) {
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glLinkProgram(shaderProgram);
    shader_program_log(shaderProgram);
    glUseProgram(shaderProgram); //this is enabling the shader by default
    return shaderProgram;
}

void bitmap_from_file(Bitmap* bmp, char* filename) {
    #ifdef __EMSCRIPTEN__
    mrgss_emsc_fetch_file(filename);
    #endif
    bmp->data = stbi_load(filename, &bmp->width, &bmp->height, &bmp->format, STBI_rgb_alpha);
    bmp->layer = -1;
    
}



int register_bitmap(GameRenderer* renderer, Bitmap* bitmap) {
    if (bitmap && bitmap->layer == -1) {
        glTexSubImage3D( GL_TEXTURE_2D_ARRAY, 0, 0, 0, renderer->txc, bitmap->width, bitmap->height ,1, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->data);
        bitmap->layer = renderer->txc;
        renderer->txc += 1; 
    }
    return bitmap->layer;
}