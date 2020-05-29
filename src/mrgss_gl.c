#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb_mage.h>
#ifndef __EMSCRIPTEN__
#include <GL/gl3w.h>
#else 
#include <GL/Regal.h>
#endif
#include <mrgss/gl.h>
#include <mrgss/structs.h>


const char* VertexShader = "#version 430 core\n"
"layout (location = 0 ) in vec2 position;\n"
"layout (location = 1 ) in vec2 texCoord;\n"
"uniform mat4 orthoView;" \
"out vec2 uv;\n"
"void main(void)\n"
"{\n"
    "gl_Position = orthoView * vec4(position.x, position.y, 0.0,1.0);\n"
    "uv = texCoord;\n"
"}\n";

const char* FragmentShader = "#version 430 core\n"
"out vec4 color;\n"
"in vec2 uv;\n"
"layout (binding=0) uniform sampler2DArray textures;\n"
//"uniform lowp float opacity;\n"
"void main(void)\n"
"{\n"
//"color = texture(textures, vec3(uv, 0));\n"
// "if(color.a <= 0.0){"
//      "discard;"
// "}"
"color = vec4(1.0, 0.0, 0.0, uv.y);"
// "  color.a *= opacity;\n"
"}\n";


static void shader_log(GLuint shaderId){
    GLint bufflen;
    GLchar* log;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &bufflen);
    log = malloc(sizeof (GLchar) * bufflen);
    glGetShaderInfoLog(shaderId, bufflen, 0, log);
    printf("shader compiling log: %s\n", log);
}

static void shader_program_log(GLuint shaderId){
    GLint bufflen;
    GLchar* log;
    glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &bufflen);
    log = malloc(sizeof (GLchar) * bufflen);
    glGetProgramInfoLog(shaderId, bufflen, 0, log);
    printf("shader program linking log: %s\n", log);
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
    bmp->data = stbi_load(filename, &bmp->width, &bmp->height, &bmp->format, STBI_rgb_alpha);
}