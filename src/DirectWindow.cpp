#include "DirectWindow.h"
#include "DirectRender.hpp"
namespace BEbraEngine {
	HWND DirectWindow::getHandle()
	{
		return glfwGetWin32Window(handle);
	}
	void DirectWindow::Resize(int w, int h)
	{
	}

	void DirectWindow::Resize(const Vector2& newSize)
	{
	}

	void DirectWindow::CreateWindow(const Vector2& size, const std::string& title)
	{
		onCreateWindow(size, BaseWindow::DirectX, title);
		render = std::make_unique<DirectRender>();
		render->Create(this);
	}

	void DirectWindow::CreateWindow(int w, int h, const std::string& title)
	{
		onCreateWindow(w,h, BaseWindow::DirectX, title);
		render = std::make_unique<DirectRender>();
		render->Create(this);
	}

	void DirectWindow::onResizeCallback()
	{
	}

	void DirectWindow::onUpdateFrame()
	{
		render->Render();
	}

	DirectWindow::DirectWindow()
	{
	}

	DirectWindow::~DirectWindow()
	{
	}
}
