#pragma once
#if defined(_WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(__APPLE__)
#define GLFW_EXPOSE_NATIVE_COCOA

#endif
#if defined(_WIN32) || defined(__APPLE__) || (defined(__unix__) && !defined(__ANDROID__))
#define DESKTOP

#endif

#if defined(__ANDROID__) || defined(__APPLE__)
#define MOBILE
#endif 

#ifdef _WIN64 
//#include "ImGui/imgui.h"
//#include "ImGui/imgui-1.83/backends/imgui_impl_dx11.h"
//#include "ImGui/imgui-1.83/backends/imgui_impl_sdl.h"
//#include "ImGui/imgui-1.83/backends/imgui_impl_vulkan.h"
#endif
