module;
#include <vulkan.h>

export module CreateInfoStructures;
import Vector3;
import <vector>;

using std::vector;

namespace BEbraEngine {
	export struct RenderBufferView;
	export struct VulkanTexture;
	export class Material;
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

		static VulkanDescriptorSetInfo create(RenderBufferView* bufferView, Material& mat);

	};

	export class VulkanDescriptorPoolInfo {
	public:
		std::vector<VkDescriptorPoolSize> types;
		VkDescriptorSetLayout layout;
	};

}