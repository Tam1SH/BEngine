#pragma once
#include "stdafx.h"
#include "RenderBuffer.hpp"
#include "Vector3.hpp"
namespace BEbraEngine {

	class ColliderInfo {
	public:
		Vector3 scale;

	};
	class LightDescriptorInfo {
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
	class VulkanDescriptorPoolInfo {
	public:
		std::vector<VkDescriptorPoolSize> types;
	};
}