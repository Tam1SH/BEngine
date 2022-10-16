module;
#include <vulkan.h>
#include "platform_window.hpp"
export module Window;
import Debug;
import Input;
import Vector2;
import <vector>;
import <string>;
using std::vector;
using std::string;

namespace BEbraEngine {

	export struct Window {

		enum class Visibility {
			Windowed,
			Minimized,
			Maximized,
			FullScreen,
			Hidden
		};
		enum class FullScreenType {
			None,
			FullScreenOnWindow,
			FullScreen
		};
		enum class SurfaceType {
			Vulkan
		};

		virtual void createWindow(const Vector2& size, const std::string& title) = 0;
		virtual void onResizeCallback(int width, int height) = 0;
		bool isClose();
		bool isCollapsed();
		void setFullScreen(FullScreenType type);
		void update();
		Vector2 getSize() const noexcept;
		void setWindowSize(const Vector2& newSize) const noexcept;
		string getName() const noexcept;
		int width() const noexcept;
		int height() const noexcept;
		void setPosition(const Vector2& position) const noexcept;
		Vector2 getPosition() const noexcept;
		void vulkan_CreateSurface(VkInstance instance, VkSurfaceKHR* surface);
		vector<const char*> vulkan_GetInstanceExtensions();

		Window();

		Window(Window&&) noexcept = default;
		Window& operator=(Window&&) noexcept = default;

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		virtual ~Window();

	protected:
		WindowHandle* handle;
		void onCreateWindow(const Vector2& size, const SurfaceType& type, const std::string& title);
	private:
		SurfaceType type;
		bool _isClose;
		void _onCreateWindow(int w, int h, const SurfaceType& type, const char* title);
	};

}
