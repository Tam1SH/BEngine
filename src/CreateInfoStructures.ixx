module;
#include <vulkan.h>

export module CreateInfoStructures;
import Vector3;
import RenderBufferView;
import <vector>;

using std::vector;

namespace BEbraEngine {
	export struct VulkanTexture;
	export struct Material;
}

namespace BEbraEngine {


	export struct LightDescriptorInfo {

		enum struct Type {
			Point,
			Direction
		};

		RenderBufferView* bufferView;
		Type type;
	};

	export struct RenderObjectInfo {
	public:
		RenderBufferView* bufferView;
	};

	export struct VulkanDescriptorSetInfo {

		RenderBufferView* bufferView;

		const VulkanTexture* image;
		const VulkanTexture* specular;
		const VulkanTexture* normal;

		static VulkanDescriptorSetInfo create(RenderBufferView* bufferView, Material& mat);

	};

	export struct VulkanDescriptorPoolInfo {
	public:
		std::vector<VkDescriptorPoolSize> types;
		VkDescriptorSetLayout layout;
	};

}