#pragma once
#ifdef _WIN64
#include "stdafx.h"
#include "BaseRenderWindow.hpp"
#include <d3d11.h>
#include <d3dx11.h>
#include "AbstractRender.hpp"
#undef createWindow
namespace BEbraEngine {
	class DXRender;
	class DXWindow : public BaseWindow
	{
	public:
		HWND getHWND();
		void createWindow(const Vector2& size, const std::string& title) override;
		void onResizeCallback(int width, int height) override;
		DXWindow(AbstractRender* render);
		~DXWindow();
	private:
		DXRender* render;
	};
}
#endif

