#include "BaseRenderWindow.h"
#include "Input.hpp"
#include <vector>
#ifdef BEBRA_USE_GLFW
namespace BEbraEngine {
	enum class SurfaceType
	{
		DirectX,
		Vulkan
		//Metal - хахах, хуй там а не метал, огрызки пидарасы


	};
	void BaseWindow::Vulkan_CreateSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		glfwCreateWindowSurface(instance, handle, NULL, surface);
	}
	void BaseWindow::update() {
		glfwPollEvents();
		onUpdateFrame();
	}
	std::vector<const char*> BaseWindow::Vulkan_GetInstanceExtensions()
	{
		uint32_t count;
		auto pizda = glfwGetRequiredInstanceExtensions(&count);
		auto _names = std::vector<const char*>();
		for (int i = 0; i < count; i++) {
			if (pizda[i])
				_names.push_back(pizda[i]);
		}
		return _names;
	}
	void BaseWindow::SetWindowSize(const Vector2& newSize) const noexcept
	{
		glfwSetWindowSize(handle, newSize.x, newSize.y);
	}
	void BaseWindow::_onCreateWindow(int w, int h, const SurfaceType& type, const char* title)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		handle = glfwCreateWindow(w, h, title, NULL, NULL);
		glfwSetWindowUserPointer(handle, this);
		Input::SetWindow(handle);
	}

	void BaseWindow::onCreateWindow(const Vector2& size, const SurfaceType& type, const std::string& title)
	{
		_onCreateWindow(size.x, size.y, type, title.c_str());
	}

	void BaseWindow::onCreateWindow(int w, int h, const SurfaceType& type, const std::string& title)
	{
		_onCreateWindow(w, h, type, title.c_str());
	}

	Vector2 BaseWindow::GetWindowSize() const noexcept
	{
		int* w = 0, * h = 0;
		glfwGetWindowSize(handle, w, h);
		return Vector2(*w, *h);
	}

	int BaseWindow::Width() const noexcept
	{
		return GetWindowSize().x;
	}

	int BaseWindow::Height() const noexcept
	{
		return GetWindowSize().y;
	}

	void BaseWindow::SetPosition(const Vector2& position) const noexcept
	{
		glfwSetWindowPos(handle, position.x, position.y);
	}

	Vector2 BaseWindow::GetPosition() const noexcept
	{
		int* x = 0, * y = 0;
		glfwGetWindowPos(handle, x, y);
		return Vector2(*x, *y);
	}

	BaseWindow::BaseWindow() 
	{
		glfwInit();
	}
	BaseWindow::~BaseWindow()
	{
		glfwTerminate();
	}

}
#endif