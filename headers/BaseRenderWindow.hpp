
#include "stdafx.h"
#pragma once
#include "platform_window.hpp"
#include "Vector2.hpp"

using BE_STD::vector;
using BE_STD::string;

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
		enum class SurfaceType {
			Vulkan
			//DX12 - ну и хуетень, чем я занимаюсь
			//Metal - Метал? блять анал
		};
	public:
		virtual void createWindow(const Vector2& size, const std::string& title) = 0;
		virtual void onResizeCallback(int width, int height) = 0;
		bool isClose();
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

		BaseWindow();
		virtual ~BaseWindow();

	protected:
		WindowHandle* handle;
		void onCreateWindow(const Vector2& size, const SurfaceType& type, const std::string& title);
	private:
		SurfaceType type;
		bool _isClose;
		void _onCreateWindow(int w, int h, const SurfaceType& type, const char* title);
	};

}
