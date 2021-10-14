#pragma once
#include "platform_window.hpp"
#include "Vector2.h"
#include <string>
#include <vulkan/vulkan.h>
#include <vector>
#undef CreateWindow
namespace BEbraEngine {
	
	class BaseWindow {
	public:
		enum class Visibility {
			Windowed,
			Minimized,
			Maximized,
			FullScreen,
			Hidden
		};
		enum SurfaceType {
			DirectX,
			Vulkan
		};

	private:
		void _onCreateWindow(int w, int h, const SurfaceType& type, const char* title);
	protected:
		WindowHandle* handle;
		void onCreateWindow(const Vector2& size, const SurfaceType& type, const std::string& title);
		void onCreateWindow(int w, int h, const SurfaceType& type, const std::string& title);
	public:
		virtual void Resize(int w, int h) = 0;
		virtual void Resize(const Vector2& newSize) = 0;
		virtual void CreateWindow(const Vector2& size, const std::string& title) = 0;
		virtual void CreateWindow(int w, int h, const std::string& title) = 0;

		void update();

		Vector2 GetWindowSize() const noexcept;
		void SetWindowSize(const Vector2& newSize) const noexcept;
		int Width() const noexcept;
		int Height() const noexcept;
		void SetPosition(const Vector2& position) const noexcept;
		Vector2 GetPosition() const noexcept;

		void Vulkan_CreateSurface(VkInstance instance, VkSurfaceKHR* surface);
		std::vector<const char*> Vulkan_GetInstanceExtensions();
		virtual void onResizeCallback() = 0;
		virtual void onUpdateFrame() = 0;

		BaseWindow();

		~BaseWindow();
	};

}
