#include "stdafx.h"
#include "VulkanObjects.hpp"
#include "VkBuffer.hpp"
namespace BEbraEngine {
    void VulkanRenderObject::release()
    {
        transform.reset();
        matrix.reset();
    }

    void VulkanRenderObject::Draw(VkCommandBuffer cmd)
    {
        auto bufferVBOview = model->meshes[0].vertices_view;
        auto bufferEBOview = model->meshes[0].indices_view;
        auto VBO = static_cast<VulkanBuffer*>(bufferVBOview->buffer.get());
        auto EBO = static_cast<VulkanBuffer*>(bufferEBOview->buffer.get());
        VkDeviceSize offset[] = { 0 };
        vkCmdBindVertexBuffers(cmd, 0, 1, &VBO->self, offset);
        vkCmdBindIndexBuffer(cmd, EBO->self, 0, VK_INDEX_TYPE_UINT32);
        vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, *layout, 0, 1, &descriptor, 0, nullptr);
        vkCmdDrawIndexed(cmd, static_cast<uint32_t>(model->meshes[0].indices.size()), 1, 0, 0, 0);
    }

}