
#include "RenderObject.hpp"
namespace BEbraEngine {
    class VulkanRenderObject : public RenderObject {
    public:
        void release() override;

        ~VulkanRenderObject() {}
    public:
        void Draw(VkCommandBuffer cmd);

        VkPipelineLayout* layout;

        VkDescriptorSet descriptor;
    };


    class VulkanPointLight : public PointLight {
    public:

        VkDescriptorSet descriptor;
    };

    class VulkanDirLight : public DirectionLight {
    public:

        VkDescriptorSet descriptor;
        ~VulkanDirLight() {}
    };
}