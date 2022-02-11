#pragma once


#if defined(_WIN32) || defined(__APPLE__) || (defined(__unix__) && !defined(__ANDROID__))
#define DESKTOP

#endif


#if defined(__ANDROID__) || defined(__APPLE__)
#define MOBILE
#endif 
#if defined(_WIN64)
#define BE_NAMESPACE_STD_BEGIN namespace std { 
#define BE_NAMESPACE_STD_END }
#define BE_STD std
#endif
#if defined(__ANDROID__)
#define BE_NAMESPACE_STD_BEGIN namespace std { namespace __ndk1 { 
#define BE_NAMESPACE_STD_END } }
#define BE_STD std::__ndk1
#endif

#ifdef _WIN64 
//#include "ImGui/imgui.h"
//#include "ImGui/imgui-1.83/backends/imgui_impl_dx11.h"
//#include "ImGui/imgui-1.83/backends/imgui_impl_sdl.h"
//#include "ImGui/imgui-1.83/backends/imgui_impl_vulkan.h"
#endif
