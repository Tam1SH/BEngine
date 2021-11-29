#include "stdafx.h"
#include "GLWindow.hpp"

namespace BEbraEngine {

	void GLWindow::createWindow(const Vector2& size, const std::string& title)
	{
		onCreateWindow(size, SurfaceType::OpenGL, title);
		render->create(this);
	}

	void GLWindow::onResizeCallback(int width, int height)
	{
	}

	GLWindow::GLWindow(AbstractRender* render)
	{
		this->render = dynamic_cast<GLRender*>(render);
	}
	void GLWindow::setGLContext(SDL_GLContext context)
	{
		this->context = context;
	}
	void GLWindow::swapWindowBuffer()
	{
		SDL_GL_SwapWindow(handle);
	}
}
