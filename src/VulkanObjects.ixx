#include <vulkan/vulkan.h>



export module VulkanObjects;
import Light;
import Camera;
import RenderObject;
import DirectionLight;
import VulkanBuffer;


namespace BEbraEngine {
    
    export struct VulkanRenderObject : RenderObject {

        ~VulkanRenderObject() {}

        void draw(VkCommandBuffer cmd);

        VkPipelineLayout* layout;

        VkDescriptorSet descriptor;
    };


    export struct VulkanPointLight : Light {

        VkDescriptorSet descriptor;
    };

    export struct VulkanDirLight : DirectionLight {

        VkDescriptorSet descriptor;
        ~VulkanDirLight() {}
    };

    export struct VulkanCamera : SimpleCamera {

        VulkanCamera(const Vector2& size, const Vector3& position) : SimpleCamera(size, position) {}
        VkDescriptorSet descriptor;

    };
    
}