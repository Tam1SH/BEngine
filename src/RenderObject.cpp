#include "stdafx.h"
#include "RenderObject.hpp"
#include "Mesh1.hpp"
#include "Transform.hpp"
#include "Image.hpp"
#include "VkBuffer.hpp"
#include "RenderObjectCreator.hpp"
namespace BEbraEngine {
    /*
    
        void RenderObject::SetFactory(VulkanRenderObjectFactory* factory)
    {
        RenderObject::factory = factory;
    }
    
        RenderObject* RenderObject::New(std::shared_ptr<Transform> transform)
    {
        return factory->createObject(transform);
    }
    */

    RenderObject::RenderObject()
    {
        std::cout << "RENDER OBJECT " << this << " CREATED" << std::endl;
    }

    RenderObject::~RenderObject()
    {
        std::cout << "RENDER OBJECT " << this << " DESTROYED" << std::endl;
    }

    VulkanRenderObjectFactory* VulkanRenderObject::factory;

    void VulkanRenderObject::release()
    {
    }

    void VulkanRenderObject::recreate()
    {
        factory->CreateObjectSet(this);
    }
    void VulkanRenderObject::Draw(VkCommandBuffer cmd)
    {
        auto bufferVBO = static_cast<VulkanBuffer*>(mesh->VBO);
        auto bufferEBO = static_cast<VulkanBuffer*>(mesh->EBO);
        VkDeviceSize offset[] = { 0 };
        vkCmdBindVertexBuffers(cmd, 0, 1, &bufferVBO->self, offset);
        vkCmdBindIndexBuffer(cmd, bufferEBO->self, 0, VK_INDEX_TYPE_UINT32);
        vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, *layout, 0, 1, &descriptor, 0, nullptr);
        
        vkCmdDrawIndexed(cmd, static_cast<uint32_t>(model->meshes[0].indices.size()), 1, 0, 0, 0);
    }
    void VulkanRenderObject::SetFactory(VulkanRenderObjectFactory* factory)
    {
        VulkanRenderObject::factory = factory;
    }
}