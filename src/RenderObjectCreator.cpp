#include "stdafx.h"
#include "RenderObject.hpp"
#include "RenderObjectCreator.hpp"
#include "RenderObjectInfo.hpp"
#include "VulkanRender.hpp"
#include "ImageCreator.hpp"
#include "Mesh1.hpp"
#include "Image.hpp"
#include "Transform.hpp"
#include "DirectRender.hpp"
#include "VkBuffer.hpp"
#include "RenderBuffer.hpp"
#include "Vertex.hpp"
#include "Image.hpp"
#include "RenderObjectPool.hpp"
namespace BEbraEngine {


    

    RenderObject* VulkanRenderObjectFactory::create(VulkanRenderObjectInfo* info)
    {
        auto obj = new RenderObject();
        obj->name = "RenderObject";
        
        obj->MeshRenderer = std::unique_ptr<Mesh1>(new Mesh1());
        obj->MeshRenderer->VBO = render->CreateVertexBuffer(vertices);
        obj->MeshRenderer->EBO = render->CreateIndexBuffer(indices);
        obj->texture = std::unique_ptr<Texture>(imgsCreator->createEmptyTexture());
        obj->matBuffer = std::shared_ptr<RenderBuffer>(info->buffer);
        obj->_matBuffer = std::shared_ptr<RenderBufferView>(info->bufferView);
        obj->offset = info->offset;
        auto type_render = dynamic_cast<VulkanRender*>(render);
        if (type_render) {
            VulkanDescriptorSetInfo setinfo{};
            setinfo.sampler = obj->texture->sampler;
            setinfo.imageView = obj->texture->imageView;
            setinfo.buffer = static_cast<Buffer*>(info->buffer);
            setinfo.offset = obj->offset;
            setinfo.bufferView = info->bufferView;
            obj->descriptor = type_render->CreateDescriptor(&setinfo);
            obj->layout = &type_render->pipelineLayout;
        }
        return obj;
    }

    RenderObject* VulkanRenderObjectFactory::CreateObject(std::shared_ptr<Transform> transform)
    {
        auto _obj = _pool->get();
        if (_obj.has_value()) {
            auto renderObject = _obj.value();
            renderObject->transform = transform;
            renderObject->transform->buffer = std::shared_ptr<RenderBuffer>(renderObject->matBuffer);
            renderObject->transform->_buffer = renderObject->_matBuffer;
            return renderObject;
        }
        else
            throw std::exception();

    }
    void VulkanRenderObjectFactory::CreateObjectSet(RenderObject* obj)
    {
        auto _render = dynamic_cast<VulkanRender*>(render);
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = _render->descriptorPool;
        allocInfo.descriptorSetCount = 1;
        allocInfo.pSetLayouts = &_render->ObjectLayout;
        vkAllocateDescriptorSets(_render->GetDevice(), &allocInfo, &obj->descriptor);
        auto buffer = static_cast<Buffer*>(obj->matBuffer.get());


        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = buffer->self;
        bufferInfo.offset = 0;
        bufferInfo.range = buffer->size;

        VkDescriptorImageInfo imageInfo{};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = obj->texture->GetView();
        imageInfo.sampler = obj->texture->GetSampler();

        std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = obj->descriptor;
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &bufferInfo;


        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = obj->descriptor;
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pImageInfo = &imageInfo;
        vkUpdateDescriptorSets(_render->GetDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }

    VulkanRenderObjectFactory::VulkanRenderObjectFactory(AbstractRender* render) : render(render)
    {
        RenderObject::SetFactory(this);

        _pool = std::make_unique<VulkanRenderObjectPool>();
        _pool->setContext(render);
        _pool->setFactory(this);
        imgsCreator = new ImageCreator(render);
        _pool->allocate(10);
    }
}