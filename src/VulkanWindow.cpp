#include "stdafx.h"
#define NOMINMAX
#include "VulkanWindow.hpp"
#include "VulkanRender.hpp"
#undef CreateWindow

namespace BEbraEngine {

	void VulkanWindow::createWindow(const Vector2& size, const std::string& title)
	{
		onCreateWindow(size, BaseWindow::SurfaceType::Vulkan, title);
		render->create(this);
	}

	VulkanWindow::VulkanWindow(AbstractRender* render)
	{
		this->render = static_cast<VulkanRender*>(render);
	}



	void VulkanWindow::onResizeCallback(int width, int height)
	{
		render->recreateSwapChain(width, height);
		render->drawFrame();
	}

	Vector2 VulkanWindow::getDrawableSize()
	{
		Vector2 vec;
		vec = getSize();
		return vec;
	}



	VulkanWindow::~VulkanWindow()
	{
	}


}