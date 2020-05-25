#ifndef MRB_MRGSS_TYPES_SCREEN_H
#define MRB_MRGSS_TYPES_SCREEN_H
#ifndef __EMSCRIPTEN__
#include <GL/gl3w.h>
#endif
#include <mrgss/structs.h>

int window_create(MR_Screen *buffer,const char* title, MR_Rect* rect, GLboolean fullscreen);
void window_show(MR_Screen *screen);
void window_update(MR_Screen *screen);
void window_swapbuffers(MR_Screen *screen);
int window_should_close(MR_Screen* screen);
void window_destroy(MR_Screen *screen);
void window_set_context(MR_Screen* screen, MR_Context* context);
MR_Context* window_get_context(GLFWwindow* window);

#endif