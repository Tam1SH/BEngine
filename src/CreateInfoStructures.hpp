#include "stdafx.h"
#include "RenderBuffer.hpp"
#include "VkBuffer.hpp"
namespace BEbraEngine {
	class RenderObjectInfo {
	public:
		RenderBufferView* bufferView;
	};

	class VulkanDescriptorSetInfo {
	public:
		RenderBufferView* bufferView;
		VkSampler sampler;
		VkImageView imageView;
	};
}