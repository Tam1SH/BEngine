#include "stdafx.h"
#include "BaseRenderWindow.hpp"
#include "Input.hpp"
#include "Vector2.hpp"
#include <SDL_vulkan.h>
#include "Debug.hpp"
#ifdef BEBRA_USE_SDL
namespace BEbraEngine {
	void BaseWindow::vulkan_CreateSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		SDL_Vulkan_CreateSurface(handle, instance, surface);

	}
	vector<const char*> BaseWindow::vulkan_GetInstanceExtensions()
	{
		unsigned int count;
		SDL_Vulkan_GetInstanceExtensions(handle, &count, nullptr);

		vector<const char*> extensions = { };
		size_t additional_extension_count = extensions.size();
		extensions.resize(additional_extension_count + count);

		SDL_Vulkan_GetInstanceExtensions(handle, &count, extensions.data() + additional_extension_count);
		return extensions;
	}
	void BaseWindow::setWindowSize(const Vector2& newSize) const noexcept
	{
		SDL_SetWindowSize(handle, newSize.x, newSize.y);
	}
	string BaseWindow::getName() const noexcept
	{
		return SDL_GetWindowTitle(handle);
	}
	void BaseWindow::update() {

		SDL_Event event;


		Input::InputState state{};
		int x{}, y{};




		//SDL_WarpMouseInWindow(handle, getSize().x / 2, getSize().y / 2);
		while (SDL_PollEvent(&event)) {

			//    ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
				auto size = getSize();

				this->onResizeCallback(size.x, size.y);
				//break;
			}
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
				_isClose = true;
			}

		}

		SDL_GetMouseState(&x, &y);

		//float deltaX = (float)x - getSize().x / 2;
		//float deltaY = getSize().y / 2 - (float)y;
		//*Input::lastX = deltaX;
		//*Input::lastY = deltaY;
		state.x = x;
		state.y = y;

		Input::update(state);
		Input::state = SDL_GetKeyboardState(NULL);


	}
	void BaseWindow::_onCreateWindow(int w, int h, const SurfaceType& type, const char* title)
	{
		SDL_WindowFlags flag{};
		if (type == SurfaceType::Vulkan) {
			flag = SDL_WINDOW_VULKAN;
		}
		handle = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flag | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

		//SDL_SetRelativeMouseMode(SDL_TRUE);
		//SDL_ShowCursor(0);
		//SDL_SetWindowGrab(handle, SDL_TRUE);

		Input::setWindow(handle);
	}
	void BaseWindow::onCreateWindow(const Vector2& size, const SurfaceType& type, const std::string& title = "BEbraEngine")
	{
		_isClose = false;
		this->type = type;
		_onCreateWindow(size.x, size.y, type, title.c_str());
	}



	Vector2 BaseWindow::getSize() const noexcept
	{
		int w = 0, h = 0;
		SDL_GetWindowSize(handle, &w, &h);
		return Vector2(w, h);
	}

	int BaseWindow::width() const noexcept
	{
		return getSize().x;
	}

	int BaseWindow::height() const noexcept
	{
		return getSize().y;
	}

	void BaseWindow::setPosition(const Vector2& position) const noexcept
	{
		SDL_SetWindowPosition(handle, position.x, position.y);
	}

	Vector2 BaseWindow::getPosition() const noexcept
	{
		int x = 0, y = 0;
		SDL_GetWindowPosition(handle, &x, &y);
		return Vector2(x, y);
	}

	BaseWindow::BaseWindow()
	{
		SDL_Init(SDL_INIT_VIDEO);
	}

	BaseWindow::~BaseWindow()
	{
		SDL_DestroyWindow(handle);
		SDL_Quit();
	}

	bool BaseWindow::isClose() {
		return _isClose;
	}

	bool BaseWindow::isCollapsed()
	{
		return SDL_GetWindowFlags(handle) & SDL_WINDOW_MINIMIZED;
	}
	void BaseWindow::setFullScreen(FullScreenType type)
	{
		int flags{};
		if (type == FullScreenType::FullScreenOnWindow)
			flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (type == FullScreenType::FullScreen)
			flags = SDL_WINDOW_FULLSCREEN;
		if (!SDL_SetWindowFullscreen(handle, flags)) throw std::exception();

	}




}
#endif