#include <vulkan/vulkan.h>

export module VulkanObjects;
import RenderObjects;
import VulkanBuffer;
import Camera;
import Vector2;
import Vector3;


namespace BEbraEngine {
    
    export class VulkanRenderObject final : public RenderObject {

    public:

        ~VulkanRenderObject() {}

        void draw(VkCommandBuffer cmd);

        VkPipelineLayout* layout;

        VkDescriptorSet descriptor;
    };


    export class VulkanPointLight : public Light {
    public:

        VkDescriptorSet descriptor;
    };

    export class VulkanDirLight : public DirectionLight {
    public:

        VkDescriptorSet descriptor;
        ~VulkanDirLight() {}
    };

    export class VulkanCamera : public SimpleCamera {
    public:
        VulkanCamera(const Vector2& size, const Vector3& position) : SimpleCamera(size, position) {}
        VkDescriptorSet descriptor;

    };
    
}