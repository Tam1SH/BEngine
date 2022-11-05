module;
#include <variant>
export module VulkanWindow;
import Render;
import Window;
import VulkanRender;
import Vector2;
import <string>;

using std::string;

namespace BEbraEngine {

	export struct VulkanWindow : Window {

		void createWindow(const Vector2& size, const std::string& title = "BEbraEngine") override;

		void onResizeCallback(int width, int height) override;

		Vector2 getDrawableSize();

		VulkanWindow() {}
		VulkanWindow(VulkanRender& render);
		~VulkanWindow();

		VulkanWindow(VulkanWindow&&) noexcept = default;
		VulkanWindow& operator=(VulkanWindow&&) noexcept = default;

		VulkanWindow(const VulkanWindow&) = delete;
		VulkanWindow& operator=(const VulkanWindow&) = delete;

	private:
		VulkanRender* render;
	};


	namespace create {

		export std::variant<VulkanWindow> window(Render& render) {

			return std::visit([](VulkanRender& render) {
				return std::variant<VulkanWindow>(render);
			}, render);
		}
	}
	/*
	void VulkanWindow::createWindow(const Vector2& size, const std::string& title)
	{
	}

	void VulkanWindow::onResizeCallback(int width, int height)
	{
	}

	Vector2 VulkanWindow::getDrawableSize()
	{
		return Vector2();
	}

	VulkanWindow::VulkanWindow(VulkanRender& render)
	{
	}

	VulkanWindow::~VulkanWindow()
	{
	}
	*/
}

