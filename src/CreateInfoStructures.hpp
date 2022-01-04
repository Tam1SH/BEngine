#pragma once
#include "stdafx.h"
#include "RenderBuffer.hpp"
#include "Vector3.hpp"
namespace BEbraEngine {


	class LightDescriptorInfo {
	public:
		enum class Type {
			Point,
			Direction
		};
	public:
		RenderBufferView* bufferView;
		Type type;
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
		VkDescriptorSetLayout layout;
	};
}