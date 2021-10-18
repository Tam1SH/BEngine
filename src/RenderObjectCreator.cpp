#include "RenderObjectCreator.hpp"
#include "RenderObject.h"
#include "VulkanRender.h"
#include "Mesh1.h"
#include "Transform.hpp"
//TODO: пересмотреть создания буфферов и создание граф. объекта.
namespace BEbraEngine {
    template<typename T>
    Buffer RenderObjectFactory::CreateBuffer(std::vector<T>& data, VkBufferUsageFlags usage, VkCommandBuffer& cmdBuffer)
    {
        Buffer buffer{};
        VkDeviceSize bufferSize = sizeof(data[0]) * data.size();
        buffer.size = bufferSize;
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        render->_createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* _data;
        vkMapMemory(render->GetDevice(), stagingBufferMemory, 0, bufferSize, 0, &_data);
        memcpy(_data, data.data(), (size_t)bufferSize);
        vkUnmapMemory(render->GetDevice(), stagingBufferMemory);

        render->_createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | usage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffer.self, buffer.memory);
        render->copyBuffer1(stagingBuffer, buffer.self, bufferSize, cmdBuffer);

        vkDestroyBuffer(render->GetDevice(), stagingBuffer, nullptr);
        vkFreeMemory(render->GetDevice(), stagingBufferMemory, nullptr);

        return buffer;
    }

    template<typename T>
    Buffer RenderObjectFactory::CreateBuffer(std::vector<T>& data, VkBufferUsageFlags usage)
    {
        Buffer buffer{};
        VkDeviceSize bufferSize = sizeof(data[0]) * data.size();
        buffer.size = bufferSize;
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        render->_createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* _data;
        vkMapMemory(render->GetDevice(), stagingBufferMemory, 0, bufferSize, 0, &_data);
        memcpy(_data, data.data(), (size_t)bufferSize);
        vkUnmapMemory(render->GetDevice(), stagingBufferMemory);

        render->_createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | usage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffer.self, buffer.memory);
        render->copyBuffer(stagingBuffer, buffer.self, bufferSize);

        vkDestroyBuffer(render->GetDevice(), stagingBuffer, nullptr);
        vkFreeMemory(render->GetDevice(), stagingBufferMemory, nullptr);

        return buffer;
    }


    Buffer RenderObjectFactory::CreateIndexBuffer(std::vector<uint32_t> indices)
    {
        return CreateBuffer(indices, VK_BUFFER_USAGE_INDEX_BUFFER_BIT);
    }

    Buffer RenderObjectFactory::CreateVertexBuffer(std::vector<Vertex> vertices)
    {
        return CreateBuffer(vertices, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
    }


    Texture RenderObjectFactory::CreateImage(Texture img)
    {
        return img;
    }

    Buffer RenderObjectFactory::CreateIndexBuffer(std::vector<uint32_t> indices, VkCommandBuffer& cmdBuffer)
    {
        return CreateBuffer(indices, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, cmdBuffer);
    }

    Buffer RenderObjectFactory::CreateVertexBuffer(std::vector<Vertex> vertices, VkCommandBuffer& cmdBuffer)
    {
        return CreateBuffer(vertices, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, cmdBuffer);
    }
    void RenderObjectFactory::CreateSet(Buffer& uniformBuffer, VkDeviceSize size, Texture* texture, VkDescriptorSet& set)
    {

        {
            std::lock_guard g(m);
            VkDescriptorSetLayout layout = render->ObjectLayout;
            VkDescriptorSetAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
            allocInfo.descriptorPool = render->descriptorPool;
            allocInfo.descriptorSetCount = 1;
            allocInfo.pSetLayouts = &layout;
            if (VkResult result = vkAllocateDescriptorSets(render->GetDevice(), &allocInfo, &set); result != VK_SUCCESS) {
                throw std::runtime_error("ddd");
            }
        }


        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = uniformBuffer.self;
        bufferInfo.offset = 0;
        bufferInfo.range = size;

        VkDescriptorImageInfo imageInfo{};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = texture->GetView();
        imageInfo.sampler = texture->GetSampler();

        std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = set;
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &bufferInfo;


        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = set;
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pImageInfo = &imageInfo;
        vkUpdateDescriptorSets(render->GetDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }

    RenderObject* RenderObjectFactory::CreateObject(std::shared_ptr<Transform> transform)
    {

        auto obj = new RenderObject();
        obj->name = "RenderObject";
        obj->transform = transform;
        obj->layout = &render->pipelineLayout;
        obj->MeshRenderer = std::unique_ptr<Mesh1>(new Mesh1());
        obj->MeshRenderer->VBO = CreateVertexBuffer(vertices);
        obj->MeshRenderer->EBO = CreateIndexBuffer(indices);

        obj->texture = std::unique_ptr<Texture>(imgsCreator->createEmptyTexture());
        obj->matBuffer = std::shared_ptr<Buffer>(CreateUniformBuffer(sizeof(glm::mat4)));
        obj->transform->buffer = obj->matBuffer;
        obj->descriptor = new VkDescriptorSet();
        CreateObjectSet(obj);
        return obj;
    }
    void RenderObjectFactory::CreateObjectSet(RenderObject* obj)
    {
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = render->descriptorPool;
        allocInfo.descriptorSetCount = 1;
        allocInfo.pSetLayouts = &render->ObjectLayout;
        vkAllocateDescriptorSets(render->GetDevice(), &allocInfo, obj->descriptor);



        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = obj->matBuffer->self;
        bufferInfo.offset = 0;
        bufferInfo.range = obj->matBuffer->size;

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
        vkUpdateDescriptorSets(render->GetDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }
    Buffer* RenderObjectFactory::CreateUniformBuffer(VkDeviceSize size)
    {
        Buffer* buffer = new Buffer();
        buffer->size = size;
        render->_createBuffer(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer->self, buffer->memory);
        return buffer;
    }
    void RenderObjectFactory::CreateStorageBuffer(VkDeviceSize size, Buffer& buffer)
    {
        buffer.size = size;
        render->_createBuffer(size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer.self, buffer.memory);
    }

    RenderObjectFactory::RenderObjectFactory(VulkanRender* render) : render(render)
    {
        RenderObject::SetFactory(this);
        imgsCreator = new ImageCreator(render);
    }

    void RenderObjectFactory::Update(RenderObject* obj) {
        CreateObjectSet(obj);
    }
}