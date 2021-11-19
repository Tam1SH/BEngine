#pragma once
#ifdef _WIN64
#include "stdafx.h"
#include "BaseRenderWindow.hpp"
#include <d3d11.h>
#include <d3dx11.h>
#include "AbstractRender.hpp"
#undef CreateWindow
namespace BEbraEngine {
	class DXRender;
	class DXWindow : public BaseWindow
	{
	public:
		HWND getHWND();
		void CreateWindow(const Vector2& size, const std::string& title) override;
		void onResizeCallback(int width, int height) override;
		void onUpdate() override;
		DXWindow(AbstractRender* render);
		~DXWindow();
	private:
		DXRender* render;
	};
}
#endif

