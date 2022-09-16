#include <vulkan/vulkan.h>



export module VulkanObjects;
import Light;
import Camera;
import RenderObject;
import DirectionLight;
import VulkanBuffer;


namespace BEbraEngine {
    
    export class VulkanRenderObject : public RenderObject {
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