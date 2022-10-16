#include <variant>
module VulkanWindow;
import VulkanRender;
import Vector2;
namespace BEbraEngine {

	
	void VulkanWindow::createWindow(const Vector2& size, const std::string& title)
	{
		
		onCreateWindow(size, Window::SurfaceType::Vulkan, title);
		render->create(*this);
	}

	VulkanWindow::VulkanWindow(VulkanRender& render)
		: render(&render) { }

	void VulkanWindow::onResizeCallback(int width, int height)
	{
		render->recreateSwapChain(width, height);
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

namespace BEbraEngine {
	namespace create {
		template<> std::variant<VulkanWindow> window(VulkanRender& render) {
			return std::variant<VulkanWindow>(render);
		}
	}
}