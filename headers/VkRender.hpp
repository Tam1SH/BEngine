#pragma once
#include "../src/stdafx.h"
#include "AbstractRender.hpp"
#include "platform.hpp"
#include "CommandBuffer.hpp"
#include "VulkanWindow.hpp"

using BE_STD::shared_ptr;
using BE_STD::unique_ptr;
using BE_STD::vector;
using BE_STD::function;
using BE_STD::optional;
using BE_STD::map;
using BE_STD::list;
using BE_STD::string;

BE_NAMESPACE_STD_BEGIN
template<typename T, typename D>
class unique_ptr;
template<class T>
class shared_ptr;
template<class T, typename Alloc>
class list;


BE_NAMESPACE_STD_END

namespace BEbraEngine {
	class VulkanTexture;
}

namespace BEbraEngine {

	namespace Vulkan {

		class Render : public AbstractRender {
		public:

			friend class VulkanWindow;

			struct SwapChainSupportDetails {
				VkSurfaceCapabilitiesKHR capabilities;
				vector<VkSurfaceFormatKHR> formats;
				vector<VkPresentModeKHR> presentModes;
			};
		public:
			// Унаследовано через AbstractRender
			virtual void create(BaseWindow* window) override;

			virtual RenderBuffer* createIndexBuffer(vector<uint32_t> indices) override;
			virtual RenderBuffer* createVertexBuffer(vector<Vertex> vertices) override;
			virtual RenderBuffer* createUniformBuffer(uint32_t size) override;
			virtual RenderBuffer* createStorageBuffer(uint32_t size) override;
			virtual void destroyBuffer(RenderBuffer* buffer) override;
			virtual void selectMainCamera(SimpleCamera& camera) override;
			virtual void addObject(RenderObject& object) override;
			virtual void addLight(PointLight& light) override;
			virtual void removeObject(RenderObject& object) override;
			virtual void removeLight(PointLight& light) override;
			virtual void addGlobalLight(DirectionLight& globalLight) override;
			virtual void addCamera(SimpleCamera& camera) override;
			virtual void removeCamera(SimpleCamera& camera) override;
			virtual IRenderObjectFactory* getRenderObjectFactory() override;
			virtual void update() override;
			virtual void drawFrame() override;
			virtual void drawLine(const Vector3& from, const Vector3& to, const Vector3& color = Vector3(0)) override;
			virtual AbstractRender::Type getType() override;
			virtual uint32_t alignmentBuffer(uint32_t originalSize, AbstractRender::TypeBuffer type) override;

			void createSurface(VkSurfaceKHR& surface);

			Render::SwapChainSupportDetails querySwapChainSupport();

		private:
			struct QueueFamilyIndices {

				optional<uint32_t> graphicsFamily;
				optional<uint32_t> presentFamily;
				optional<uint32_t> transferFamily;
				bool isComplete() {
					return graphicsFamily.has_value() && presentFamily.has_value() && transferFamily.has_value();
				}
			};

			struct Attachments {

				vector<unique_ptr<VulkanTexture>> image;

				vector<unique_ptr<VulkanTexture>> normal;

				vector<unique_ptr<VulkanTexture>> color;

				vector<unique_ptr<VulkanTexture>> depth;

			};


		private:

			unique_ptr<Attachments> attachments;

			VulkanWindow* window;

			VkDebugUtilsMessengerEXT debugMessenger;

			tbb::concurrent_queue<CommandBuffer> BufferRenderQueue;

			tbb::concurrent_queue<CommandBuffer> BufferTransferQueue;

			VkQueue graphicsQueue;

			VkQueue transferQueue;

			VkQueue presentQueue;

			VkRenderPass pass;

			VkDescriptorSetLayout presentImageLayout;

			vector<const char*> extensions;

			VkInstance instance;

			VkDevice device;

			VkPhysicalDevice physicalDevice;

			VkPhysicalDeviceProperties deviceProperties;

			vector<VkFramebuffer> swapChainFramebuffers;

		private:
			void createInstance();

			void pickPhysicalDevice();

			void createLogicalDevice();

			void createImageViews();

			void createFrameBuffers();

			void createAttachments();

			void createRenderPass();
		private:

			uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

			void createAttachment(VkFormat format, VkImageUsageFlags usage, VulkanTexture* attachment);

			void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

			bool isDeviceSuitable(VkPhysicalDevice device);

			void setupDebugMessenger();





			VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

			bool isEnabledValidation();

			void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

			QueueFamilyIndices findQueueFamilies();

			VkFormat findSupportedFormat(const vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

			VkFormat findDepthFormat();

			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

			const vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
			};

			const vector<const char*> deviceExtensions = {
				VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};

		};

		class VkRenderWorld {
		private:

			VkDescriptorSetLayout ObjectLayout;

			VkDescriptorSetLayout WorldLayout;

		};
	}
	
}