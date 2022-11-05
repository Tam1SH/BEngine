module;
#include "platform.hpp"
#include <vulkan.h>
export module CreateInfoStructures;
import <vector>;
import RenderBuffer;
import Vector3;
import Texture;
import Material;


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

		static VulkanDescriptorSetInfo create(RenderBufferView* bufferView, Material& mat) {
			VulkanDescriptorSetInfo info{};
			info.bufferView = bufferView;
			info.image = &mat.getColor().as<VulkanTexture>();
			info.specular = &mat.getSpecular().as<VulkanTexture>();
			info.normal = &mat.getNormal().as<VulkanTexture>();
			return info;
		}

	};
	export class VulkanDescriptorPoolInfo {
	public:
		std::vector<VkDescriptorPoolSize> types;
		VkDescriptorSetLayout layout;
	};
}