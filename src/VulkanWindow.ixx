export module VulkanWindow;
import Render;
import BaseRenderWindow;
import <string>;
import Vector2;
namespace BEbraEngine {
	class VulkanRender;
}
namespace BEbraEngine {

	export class VulkanWindow : public BaseWindow {
	public:

		void createWindow(const Vector2& size, const std::string& title = "BEbraEngine") override;

		VulkanWindow(Render* render);

		void onResizeCallback(int width, int height) override;

		Vector2 getDrawableSize();

		~VulkanWindow();

	private:
		VulkanRender* render;

	};
}

