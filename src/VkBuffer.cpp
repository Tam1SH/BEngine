#include "stdafx.h"
#include "VkBuffer.hpp"
#include "VulkanRender.hpp"

namespace BEbraEngine {

    void VulkanBuffer::destroy()
    {
        vkFreeMemory(VulkanRender::device, memory, 0);
        vkDestroyBuffer(VulkanRender::device, self, 0);
        memory = 0;
        self = 0;
    }

    VulkanBuffer::~VulkanBuffer()
    {
        destroy();
    }
    void VulkanBuffer::setData(const void* data, uint32_t size, uint32_t offset)
    {
        struct ShaderData {
            alignas(16) Vector3 direction;

            //компоненты света
            alignas(16) Vector3 ambient;
            alignas(16) Vector3 diffuse;
            alignas(16) Vector3 specular;

        };
        ShaderData __data{};
        void* _data;
        
        memcpy(&_data, memory, 16);

        vkMapMemory(VulkanRender::device, memory, offset, size, 0, &_data);
        memcpy(_data, data, size);
       // memcpy(memory, &__data, sizeof(ShaderData));
        
        vkUnmapMemory(VulkanRender::device, memory);
    }
}