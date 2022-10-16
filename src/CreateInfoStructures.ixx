module;
#include "platform.hpp"
#include <vulkan.h>
export module CreateInfoStructures;
import <vector>;
import RenderBuffer;
import Vector3;
import Texture;

using BE_STD::vector;

namespace BEbraEngine {
}

namespace BEbraEngine {


	export class LightDescriptorInfo {
	public:
		enum class Type {
			Point,
			Direction
		};
	public:
		RenderBufferView* bufferView;
		Type type;
	};

	export class RenderObjectInfo {
	public:
		RenderBufferView* bufferView;
	};

	export class VulkanDescriptorSetInfo {
	public:
		RenderBufferView* bufferView;

		const VulkanTexture* image;
		const VulkanTexture* specular;
		const VulkanTexture* normal;
	};
	export class VulkanDescriptorPoolInfo {
	public:
		std::vector<VkDescriptorPoolSize> types;
		VkDescriptorSetLayout layout;
	};
}