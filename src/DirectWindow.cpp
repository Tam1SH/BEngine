#include "stdafx.h"
#include "DirectWindow.hpp"
#include "DirectRender.hpp"
#ifdef BEBRA_USE_GLFW
namespace BEbraEngine {
	HWND DirectWindow::getHandle()
	{
		return glfwGetWin32Window(handle);
	}

	void DirectWindow::CreateWindow(const Vector2& size, const std::string& title)
	{
		onCreateWindow(size, BaseWindow::DirectX, title);
		render->Create(this);
	}

	void DirectWindow::onResizeCallback(int width, int height)
	{
	}

	void DirectWindow::onUpdate()
	{
		render->Render();
	}

	DirectWindow::DirectWindow(std::shared_ptr<DirectRender> render)
	{
		this->render = render;
	}


	DirectWindow::~DirectWindow()
	{
	}
}
#endif