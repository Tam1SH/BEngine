#include "platform.h"


#ifdef DESKTOP 
#define GLFW_INCLUDE_VULKAN
#define BEBRA_USE_GLFW
#include <glfw3.h>
#include <glfw3native.h>
typedef GLFWwindow WindowHandle;
#endif

#ifdef MOBILE
#define BEBRA_USE_SDL
#include <SDL.h>
typedef SDL_Window WindowHandle;
#endif