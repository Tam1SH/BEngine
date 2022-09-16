#include <variant>
export module VulkanWindow;
import CRender;
import VulkanRender;
import Window;
import Vector2;
import <string>;

namespace BEbraEngine {

	export class VulkanWindow : public Window {
	public:

		void createWindow(const Vector2& size, const std::string& title = "BEbraEngine") override;

		void onResizeCallback(int width, int height) override;

		Vector2 getDrawableSize();

		VulkanWindow() {}
		VulkanWindow(VulkanRender& render);

		~VulkanWindow();

	private:
		VulkanRender* render;
	};


	namespace create {


		export std::variant<VulkanWindow> window(CRender auto& render) {
			static_assert("no implementation found");
		}

		export template<> std::variant<VulkanWindow> window(VulkanRender& render);

	}
}

