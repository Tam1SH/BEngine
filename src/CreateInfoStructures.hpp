#include "stdafx.h"
#include "RenderBuffer.hpp"
#include "VkBuffer.hpp"
#include "Vector3.hpp"
namespace BEbraEngine {

	class LightInfo {
	public:
		RenderBufferView* bufferView;
	};
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