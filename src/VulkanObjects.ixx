module;
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

        void draw(VkCommandBuffer cmd)
        {
            if (model) {
                auto bufferVBOview = model->meshes[0].vertices_view;
                auto bufferEBOview = model->meshes[0].indices_view;
                auto VBO = static_cast<VulkanBuffer*>(bufferVBOview->buffer.get());
                auto EBO = static_cast<VulkanBuffer*>(bufferEBOview->buffer.get());
                VkDeviceSize offset[] = { 0 };
                vkCmdBindVertexBuffers(cmd, 0, 1, &VBO->self, offset);
                vkCmdBindIndexBuffer(cmd, EBO->self, 0, VK_INDEX_TYPE_UINT32);
                if (descriptor)
                    vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, *layout, 0, 1, &descriptor, 0, nullptr);
                vkCmdDrawIndexed(cmd, static_cast<uint32_t>(model->meshes[0].indices.size()), 1, 0, 0, 0);
            }
        }

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