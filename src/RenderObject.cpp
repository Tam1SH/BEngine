#include "stdafx.h"
#include "RenderObject.hpp"
#include "Transform.hpp"
#include "Image.hpp"
#include "VkBuffer.hpp"
#include "RenderObjectCreator.hpp"
namespace BEbraEngine {
    void RenderObject::update()
    {
        ShaderData data;
        data.model = transform->getMatrix();
        data.color = color;
        matrix->setData(&data, sizeof(ShaderData));
    }
    RenderObject::RenderObject()
    {
    }

    RenderObject::~RenderObject()
    {
        matrix->buffer->Destroy();
        

    }

    VulkanRenderObjectFactory* VulkanRenderObject::factory;

    void VulkanRenderObject::release()
    {
    }

    void VulkanRenderObject::recreate()
    {
        factory->CreateObjectSet(this);
    }
    VulkanRenderObject::~VulkanRenderObject()
    {
        factory->destroyObject(this);
    }
    void VulkanRenderObject::Draw(VkCommandBuffer cmd)
    {
        auto bufferVBOview = model->meshes[0].vertices_view;
        auto bufferEBOview = model->meshes[0].indices_view;
        auto VBO = static_cast<VulkanBuffer*>(bufferVBOview->buffer);
        auto EBO = static_cast<VulkanBuffer*>(bufferEBOview->buffer);
        VkDeviceSize offset[] = { 0 };
        vkCmdBindVertexBuffers(cmd, 0, 1, &VBO->self, offset);
        vkCmdBindIndexBuffer(cmd, EBO->self, 0, VK_INDEX_TYPE_UINT32);
        vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, *layout, 0, 1, &descriptor, 0, nullptr);

        vkCmdDrawIndexed(cmd, static_cast<uint32_t>(model->meshes[0].indices.size()), 1, 0, 0, 0);
    }
    void VulkanRenderObject::SetFactory(VulkanRenderObjectFactory* factory)
    {
        VulkanRenderObject::factory = factory;
    }
}