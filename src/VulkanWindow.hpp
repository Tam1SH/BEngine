#pragma once
#include "stdafx.h"
#include "Vector2.hpp"
#include "BaseRenderWindow.hpp"
#include "VulkanRender.hpp"

#undef CreateWindow
namespace BEbraEngine {

	class VulkanWindow : public BaseWindow {
	public:

		void CreateWindow(const Vector2& size, const std::string& title = "BEbraEngine") override;

		VulkanWindow(std::shared_ptr<VulkanRender> render) { this->render = std::shared_ptr<VulkanRender>(render); }

		AbstractRender* getRender();

		void onResizeCallback(int width, int height) override;

		Vector2 GetDrawableSize();

		void SetVulkanRender(VulkanRender* render);

		void onUpdate() override;

		~VulkanWindow();

	private:
		std::shared_ptr<VulkanRender> render;

	};
}

