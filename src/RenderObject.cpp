#include "RenderObject.h"
#include "Mesh1.h"
#include "Transform.hpp"
#include "Image.hpp"
#include "VkBuffer.hpp"
#include "RenderObjectCreator.hpp"
namespace BEbraEngine {
    RenderObjectFactory* RenderObject::factory;

    void RenderObject::SetFactory(RenderObjectFactory* factory)
    {
        RenderObject::factory = factory;
    }

    RenderObject::RenderObject()
    {
        std::cout << "RENDER OBJECT " << this << " CREATED" << std::endl;
    }

    RenderObject* RenderObject::New(std::shared_ptr<Transform> transform)
    {
        return factory->CreateObject(transform);
    }

    void RenderObject::Draw(VkCommandBuffer cmd)
    {
        auto bufferVBO = static_cast<Buffer*>(MeshRenderer->VBO);
        auto bufferEBO = static_cast<Buffer*>(MeshRenderer->EBO);
        VkDeviceSize offset[] = { 0 };
        vkCmdBindVertexBuffers(cmd, 0, 1, &bufferVBO->self, offset);
        vkCmdBindIndexBuffer(cmd, bufferEBO->self, 0, VK_INDEX_TYPE_UINT32);
        vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, *layout, 0, 1, descriptor, 0, nullptr);
        vkCmdDrawIndexed(cmd, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
    }

    void RenderObject::Recreate()
    {
        factory->CreateObjectSet(this);
    }

    RenderObject::~RenderObject()
    {
        delete descriptor;
        std::cout << "RENDER OBJECT " << this << " DESTROYED" << std::endl;
    }
}