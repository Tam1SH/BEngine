#include "RenderObjectCreator.hpp"
#include "RenderObject.h"
#include "VulkanRender.h"
#include "Mesh1.h"
#include "Transform.hpp"
#include "DirectRender.hpp"
#include "RenderBuffer.hpp"
//TODO: пересмотреть создания буфферов и создание граф. объекта.
namespace BEbraEngine {


    Texture RenderObjectFactory::CreateImage(Texture img)
    {
        return img;
    }
    

    RenderObject* RenderObjectFactory::CreateObject(std::shared_ptr<Transform> transform)
    {

        auto obj = new RenderObject();
        obj->name = "RenderObject";
        obj->transform = transform;

        obj->MeshRenderer = std::unique_ptr<Mesh1>(new Mesh1());

        obj->MeshRenderer->VBO = render->CreateVertexBuffer(vertices);
        obj->MeshRenderer->EBO = render->CreateIndexBuffer(indices);
        if(!dynamic_cast<DirectRender*>(render))
            obj->texture = std::unique_ptr<Texture>(imgsCreator->createEmptyTexture());
        obj->matBuffer = std::shared_ptr<RenderBuffer>(render->CreateUniformBuffer(sizeof(glm::mat4)));
        obj->transform->buffer = obj->matBuffer;
        auto type_render = dynamic_cast<VulkanRender*>(render);
        if (type_render) {
            obj->descriptor = new VkDescriptorSet();
            obj->layout = &type_render->pipelineLayout;

            CreateObjectSet(obj);
        }
        return obj;
    }
    void RenderObjectFactory::CreateObjectSet(RenderObject* obj)
    {
        auto _render = dynamic_cast<VulkanRender*>(render);
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = _render->descriptorPool;
        allocInfo.descriptorSetCount = 1;
        allocInfo.pSetLayouts = &_render->ObjectLayout;
        vkAllocateDescriptorSets(_render->GetDevice(), &allocInfo, obj->descriptor);
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
        descriptorWrites[0].dstSet = *obj->descriptor;
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &bufferInfo;


        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = *obj->descriptor;
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pImageInfo = &imageInfo;
        vkUpdateDescriptorSets(_render->GetDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }
    void RenderObjectFactory::CreateStorageBuffer(VkDeviceSize size, Buffer& buffer)
    {
        auto _render = dynamic_cast<VulkanRender*>(render);
        buffer.size = size;
        _render->_createBuffer(size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer.self, buffer.memory);
    }

    RenderObjectFactory::RenderObjectFactory(AbstractRender* render) : render(render)
    {
        RenderObject::SetFactory(this);
        imgsCreator = new ImageCreator(render);
    }

    void RenderObjectFactory::Update(RenderObject* obj) {
        CreateObjectSet(obj);
    }
}