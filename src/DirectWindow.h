#pragma once
#ifdef _WIN64
#include "BaseRenderWindow.h"
#include <memory>
#include <d3d11.h>
#include <d3dx11.h>
#undef CreateWindow
namespace BEbraEngine {
	class DirectRender;
	class DirectWindow : public BaseWindow
	{
	private:
		std::unique_ptr<DirectRender> render;
	public:
		HWND getHandle();
		void Resize(int w, int h) override;
		void Resize(const Vector2& newSize) override;
		void CreateWindow(const Vector2& size, const std::string& title) override;
		void CreateWindow(int w, int h, const std::string& title) override;
		void onResizeCallback() override;
		void onUpdateFrame() override;
		DirectWindow();
		~DirectWindow();
	};
}
#endif

