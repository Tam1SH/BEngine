#pragma once
#include "stdafx.h"
#include "Vector2.hpp"
#include "BaseRenderWindow.hpp"
#include "AbstractRender.hpp"

namespace BEbraEngine {
	class VulkanRender;
}
namespace BEbraEngine {

	class VulkanWindow : public BaseWindow {
	public:

		void createWindow(const Vector2& size, const std::string& title = "BEbraEngine") override final;

		VulkanWindow(AbstractRender* render);

		void onResizeCallback(int width, int height) override;

		Vector2 getDrawableSize();

		~VulkanWindow();

	private:
		VulkanRender* render;

	};
}

