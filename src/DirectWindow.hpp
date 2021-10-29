#pragma once
#ifdef _WIN64
#include "stdafx.h"
#include "BaseRenderWindow.hpp"
#include <d3d11.h>
#include <d3dx11.h>
#include "AbstractRenderSystem.hpp"
#undef CreateWindow
namespace BEbraEngine {
	class DirectRender;
	class DirectWindow : public BaseWindow
	{
	public:
		HWND getHandle();
		void CreateWindow(const Vector2& size, const std::string& title) override;
		void onResizeCallback(int width, int height) override;
		void onUpdate() override;
		DirectWindow(std::shared_ptr<DirectRender> render);
		~DirectWindow();
	private:
		std::shared_ptr<DirectRender> render;
	};
}
#endif

