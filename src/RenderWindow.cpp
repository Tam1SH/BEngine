#include "RenderWindow.hpp"
#include <iostream>
namespace BEbraEngine {
	void RenderWindow::CreateSurface()
	{
		SDL_Vulkan_CreateSurface(window, BaseVulkanRender::instance, &render->surface);
		//glfwCreateWindowSurface(BaseVulkanRender::instance, window, 0, &render->surface);
	}


	/*

	void RenderWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto renderWindow = reinterpret_cast<RenderWindow*>(glfwGetWindowUserPointer(window));
		renderWindow->Resize();
		renderWindow->render->recreateSwapChain();

		renderWindow->render->UpdateFrame();
	}
	*/

	void RenderWindow::Resize()
	{
		/*

		int width = 0, height = 0;
		glfwGetFramebufferSize(window, &width, &height);
		while (width == 0 || height == 0) {
			glfwGetFramebufferSize(window, &width, &height);
			glfwWaitEvents();
		}
		*/
	}


	void RenderWindow::ResizeCallback()
	{
		render->recreateSwapChain();

		render->UpdateFrame();
	}

	SDL_Window* RenderWindow::GetHandle()
	{
		return window;
	}

	void RenderWindow::SetRender(BaseVulkanRender* render) {
		this->render = render;
	}

	RenderWindow::RenderWindow()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("BEBRAAAAAAAAAAA!!!!!!!!!!!", 0, 0, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
		if (window == nullptr) {
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		}
		Input::SetWindow(window);
		Input::SetKeyBoardState(SDL_GetKeyboardState(NULL));
	}

	RenderWindow::~RenderWindow()
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void BaseWindow::SetSurfaceType(SurfaceType type) noexcept
	{
		this->type = type;
	}

	void BaseWindow::CreateWindow(const Vector& position, const Vector& size, const std::string& title)
	{
		const char* str;
		if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)){
			str = SDL_GetError();
		}
		handle = SDL_CreateWindow("SUKA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 480,   SDL_WINDOW_VULKAN);
		if (handle) {
			Input::SetWindow(handle);
			Input::SetKeyBoardState(SDL_GetKeyboardState(NULL));
		}
		else {
			str = SDL_GetError();
		}
	}

	void BaseWindow::CreateWindow(int x, int y, int w, int h, const std::string& title)
	{

		SDL_Init(SDL_INIT_VIDEO);
		handle = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | type);
		Input::SetWindow(handle);
		Input::SetKeyBoardState(SDL_GetKeyboardState(NULL));

	}

	Vector BaseWindow::GetWindowSize() const noexcept
	{
		int* w = 0, *h = 0;
		SDL_GetWindowSize(handle, w, h);
		return Vector(*w, *h);
	}

	int BaseWindow::Width() const noexcept
	{
		return GetWindowSize().x;
	}

	int BaseWindow::Height() const noexcept
	{
		return GetWindowSize().y;
	}

	void BaseWindow::SetPosition(const Vector& position) const noexcept
	{
		SDL_SetWindowPosition(handle, position.x, position.y);
	}

	Vector BaseWindow::GetPosition() const noexcept
	{
		int* x = 0, *y = 0;
		SDL_GetWindowPosition(handle, x, y);
		return Vector(*x,*y);
	}

	SDL_Window* BaseWindow::GetHandle() const noexcept
	{
		return handle;
	}

}