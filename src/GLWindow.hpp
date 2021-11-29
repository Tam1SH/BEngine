#pragma once
#if !defined(__APPLE__)
#include "BaseRenderWindow.hpp"
#include "GLRender.hpp"
namespace BEbraEngine {

	class GLWindow : public BaseWindow
	{
	public:
		void createWindow(const Vector2& size, const std::string& title) override;
		void onResizeCallback(int width, int height) override;
		GLWindow(AbstractRender* render);
		void setGLContext(SDL_GLContext context);
		void swapWindowBuffer();
	private:
		GLRender* render;
		SDL_GLContext context;
	};
}
#endif
