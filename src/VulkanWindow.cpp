#define NOMINMAX
#include "VulkanWindow.h"
#include <memory>
#undef CreateWindow

namespace BEbraEngine {

	void VulkanWindow::CreateWindow(const Vector2& size, const std::string& title)
	{
		onCreateWindow(size, BaseWindow::SurfaceType::Vulkan, title);
		render = std::make_unique<VulkanRender>();
		render->Create(this);
	}

	void VulkanWindow::CreateWindow(int w, int h, const std::string& title)
	{
		onCreateWindow(w, h, BaseWindow::SurfaceType::Vulkan, title);
		render = std::make_unique<VulkanRender>();
		render->Create(this);
	}

	VulkanRender* VulkanWindow::GetRender()
	{
		return render.get();
	}

	void VulkanWindow::onResizeCallback(int width, int height)
	{
		render->recreateSwapChain(width, height);
		render->UpdateFrame();
	}

	Vector2 VulkanWindow::GetDrawableSize()
	{
		Vector2 vec;
		vec = GetWindowSize();
		return vec;
	}

	void VulkanWindow::onUpdate()
	{

		render->UpdateFrame();
	}

	VulkanWindow::~VulkanWindow()
	{
	}

	void VulkanWindow::SetVulkanRender(VulkanRender* render)
	{
		//SDL_Vulkan_CreateSurface(handle, BaseVulkanRender::instance, &render->surface);
	}
}