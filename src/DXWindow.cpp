#include "stdafx.h"
#include "DirectWindow.hpp"
#include "DXRender.hpp"
#include <SDL/SDL_syswm.h>
namespace BEbraEngine {
	HWND DXWindow::getHWND()
	{
		SDL_SysWMinfo info{};
		SDL_GetWindowWMInfo(handle, &info);
		return info.info.win.window;
	}

	void DXWindow::createWindow(const Vector2& size, const std::string& title)
	{
		onCreateWindow(size, BaseWindow::SurfaceType::DirectX, title);
		render->create(this);
	}

	void DXWindow::onResizeCallback(int width, int height)
	{
	}


	DXWindow::DXWindow(AbstractRender* render)
	{
		this->render = dynamic_cast<DXRender*>(render);
	}


	DXWindow::~DXWindow()
	{
	}
}