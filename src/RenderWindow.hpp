#pragma once

#include <SDL.h>
#include "Input.hpp"
#include "Vector.h"
#include <vector>
#include <vulkan/vulkan.h>
#include "BaseVulkanRender.hpp"
#include "VulkanRender.h"
#undef CreateWindow
namespace BEbraEngine {

	class BaseWindow {
	public:
		enum Visibility {
			Windowed,
			Minimized,
			Maximized,
			FullScreen,
			Hidden
		};
		enum SurfaceType {
			DirectX,
			Vulkan = 0x10000000

		};
	protected:
		SDL_Window* handle;
	private:
		SurfaceType type;
	public:
		virtual void Resize(int w, int h) = 0;
		virtual void Resize(const Vector& newSize) = 0;

		//xyu znaet 
		//virtual void isHide() = 0;
		//virtual void isClose() = 0;
		void SetSurfaceType(SurfaceType type) noexcept;

		void CreateWindow(const Vector& position, const Vector& size, const std::string& title = "BEbraEngine");
		void CreateWindow(int x, int y, int w, int h, const std::string& title = "BEbraEngine");
		Vector GetWindowSize() const noexcept;
		int Width() const noexcept;
		int Height() const noexcept;
		void SetPosition(const Vector& position) const noexcept;
		Vector GetPosition() const noexcept;
		SDL_Window* GetHandle() const noexcept;
		virtual void ResizeCallback() = 0;
		virtual void UpdateFrame() = 0;
	};

	class VulkanWindow : public BaseWindow {
	private:
		std::unique_ptr<VulkanRender> render;

	public:


		VulkanWindow() { }

		void InitRender() {
			render = std::make_unique<VulkanRender>();

			render->window = this;
			render->createInstance();
			SDL_Vulkan_CreateSurface(handle, BaseVulkanRender::instance, &render->surface);
			render->initRender();
			render->Init();
		}
		VulkanRender* GetRender() {
			return render.get();
		}
		void ResizeCallback() override {
			render->recreateSwapChain();
		}
		void GetInstanceExtensions(unsigned int* pCount, const char** pNames) {
			SDL_Vulkan_GetInstanceExtensions(handle, pCount, pNames);
		}
		Vector GetDrawableSize() {
			int* w = 0, *h = 0;
			SDL_Vulkan_GetDrawableSize(handle, w, h);
			return Vector(*w, *h);
		}

		void SetVulkanRender(BaseVulkanRender* render) {
			//this->render = render;
			SDL_Vulkan_CreateSurface(handle, BaseVulkanRender::instance, &render->surface);
		}

		void Resize(int w, int h)  override {
			SDL_SetWindowSize(handle, w, h);
			render->recreateSwapChain();
		}
		void Resize(const Vector& newSize)  override {
			SDL_SetWindowSize(handle, newSize.x, newSize.y);
			render->recreateSwapChain();
		}
		void UpdateFrame() override {
			render->UpdateFrame();
		}
		~VulkanWindow() {
			SDL_DestroyWindow(handle);
			SDL_Quit();
		}
	};

	//DEPRESED BLA)

	class RenderWindow
	{
	private:
		SDL_Window* window;
		BaseVulkanRender* render;

	public:

		void Resize();

		void ResizeCallback();

		void CreateSurface();

		SDL_Window* GetHandle();

		void SetRender(BaseVulkanRender* render);

		RenderWindow();

		~RenderWindow();

	};
}

