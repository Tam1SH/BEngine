#include "VulkanWindow.h"
#include <memory>
#undef CreateWindow
namespace BEbraEngine {

	void VulkanWindow::CreateWindow(const Vector2& size, const std::string& title)
	{
		onCreateWindow(size, BaseWindow::SurfaceType::Vulkan, title);
		render = std::make_unique<VulkanRender>();
		render->window = this;
		render->createInstance();
		Vulkan_CreateSurface(BaseVulkanRender::instance, &render->surface);
		render->initRender();
		render->Init();
	}

	void VulkanWindow::CreateWindow(int w, int h, const std::string& title)
	{
		onCreateWindow(w, h, BaseWindow::SurfaceType::Vulkan, title);
		render = std::make_unique<VulkanRender>();
		render->window = this;
		render->createInstance();
		Vulkan_CreateSurface(BaseVulkanRender::instance, &render->surface);
		render->initRender();
		//render->Init();
	}
	VulkanRender* VulkanWindow::GetRender()
	{
		return render.get();
	}
	void VulkanWindow::onResizeCallback()
	{
		render->recreateSwapChain();
	}
	Vector2 VulkanWindow::GetDrawableSize()
	{
		Vector2 vec;
		vec = GetWindowSize();

		//SDL_Vulkan_GetDrawableSize(handle, w, h);
		return vec;
	}
	void VulkanWindow::Resize(int w, int h)
	{
		//SDL_SetWindowSize(handle, w, h);
		SetWindowSize(Vector2(w, h));
		render->recreateSwapChain();
	}
	void VulkanWindow::Resize(const Vector2& newSize)
	{
		SetWindowSize(newSize);

		render->recreateSwapChain();
	}

	void VulkanWindow::onUpdateFrame()
	{

		render->UpdateFrame();
	}

	VulkanWindow::~VulkanWindow()
	{
		//SDL_DestroyWindow(handle);
		//SDL_Quit();
		//glfwTerminate();

	}

	void VulkanWindow::SetVulkanRender(VulkanRender* render)
	{
		//SDL_Vulkan_CreateSurface(handle, BaseVulkanRender::instance, &render->surface);
	}
}