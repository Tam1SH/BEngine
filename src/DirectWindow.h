#pragma once
#ifdef _WIN64
#include "BaseRenderWindow.h"
#include <memory>
#include <d3d11.h>
#include <d3dx11.h>
#include "AbstractRenderSystem.hpp"
#undef CreateWindow
namespace BEbraEngine {
	class DirectRender;
	class DirectWindow : public BaseWindow
	{
	private:
		std::unique_ptr<DirectRender> render;
	public:
		HWND getHandle();
		void CreateWindow(const Vector2& size, const std::string& title) override;
		void CreateWindow(int w, int h, const std::string& title) override;
		void onResizeCallback(int width, int height) override;
		void onUpdate() override;
		AbstractRender* getRender();
		DirectWindow();
		~DirectWindow();
	};
}
#endif

