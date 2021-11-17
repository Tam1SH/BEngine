#include "stdafx.h"
#pragma once
#include "platform_window.hpp"
#include "Vector2.hpp"
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
			OpenGL,
			Vulkan
			//Metal - Метал? блять анал
		};
	public:
		virtual void CreateWindow(const Vector2& size, const std::string& title) = 0;
		virtual void onResizeCallback(int width, int height) = 0;
		virtual void onUpdate() = 0;

		bool isClose();
		void update();
		Vector2 GetWindowSize() const noexcept;
		void SetWindowSize(const Vector2& newSize) const noexcept;
		int Width() const noexcept;
		int Height() const noexcept;
		void SetPosition(const Vector2& position) const noexcept;
		Vector2 GetPosition() const noexcept;

		


		BaseWindow();
		virtual ~BaseWindow();

		void Vulkan_CreateSurface(VkInstance instance, VkSurfaceKHR* surface);
		std::vector<const char*> Vulkan_GetInstanceExtensions();

	protected:
		WindowHandle* handle;
		void onCreateWindow(const Vector2& size, const SurfaceType& type, const std::string& title);
	private:
		bool _isClose;
		void _onCreateWindow(int w, int h, const SurfaceType& type, const char* title);
	};

}
