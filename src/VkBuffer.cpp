#include "stdafx.h"
#include "VkBuffer.hpp"
#include "VulkanRender.hpp"
//TODO: сделать не зависимым от граф. апи.
namespace BEbraEngine {

    void VulkanBuffer::Destroy()
    {
        vkFreeMemory(VulkanRender::device, memory, 0);
        vkDestroyBuffer(VulkanRender::device, self, 0);
        memory = 0;
        self = 0;
    }

    VulkanBuffer::~VulkanBuffer()
    {
        Destroy();
    }
    void VulkanBuffer::setData(void* data, size_t size, size_t offset)
    {
        void* _data;
        vkMapMemory(VulkanRender::device, memory, offset, size, 0, &_data);
        memcpy(_data, data, size);
        vkUnmapMemory(VulkanRender::device, memory);
    }
}