#include "stdafx.h"
#include "RenderBuffer.hpp"
#include "VkBuffer.hpp"
namespace BEbraEngine {
	class VulkanRenderObjectInfo {
	public:
		size_t size;
		size_t offset;
		RenderBuffer* buffer;
		RenderBufferView* bufferView;
	};
	class VulkanDescriptorSetInfo {
	public:
		Buffer* buffer;
		RenderBufferView* bufferView;
		size_t offset;
		VkSampler sampler;
		VkImageView imageView;
	};
}