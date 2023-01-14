module CreateInfoStructures;
import Material;
import Texture;

namespace BEbraEngine {
	VulkanDescriptorSetInfo VulkanDescriptorSetInfo::create(RenderBufferView* bufferView, Material& mat)
	{
		VulkanDescriptorSetInfo info{};
		info.bufferView = bufferView;
		info.image = &mat.getColor().as<VulkanTexture>();
		info.specular = &mat.getSpecular().as<VulkanTexture>();
		info.normal = &mat.getNormal().as<VulkanTexture>();
		return info;
	}
}