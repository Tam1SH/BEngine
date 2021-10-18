#pragma once
#include "Vector2.h"
#include "BaseRenderWindow.h"
#include "VulkanRender.h"
#undef CreateWindow
namespace BEbraEngine {

	class VulkanWindow : public BaseWindow {
	private:
		std::unique_ptr<VulkanRender> render;

	public:

		void CreateWindow(const Vector2& size, const std::string& title = "BEbraEngine") override;

		void CreateWindow(int w, int h, const std::string& title = "BEbraEngine") override;

		VulkanWindow() {}

		VulkanRender* GetRender();

		void onResizeCallback(int width, int height) override;

		Vector2 GetDrawableSize();

		void SetVulkanRender(VulkanRender* render);

		void onUpdate() override;

		~VulkanWindow();

	};
}

