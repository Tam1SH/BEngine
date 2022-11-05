#include <vulkan.h>
module VulkanBuffer;
import VulkanRender;

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
       //destroy();
    }
    void VulkanBuffer::setData(const void* data, uint32_t size, uint32_t offset)
    {
       void* _data;
        
       vkMapMemory(VulkanRender::device, memory, offset, size, 0, &_data);
       memcpy(_data, data, size);
       vkUnmapMemory(VulkanRender::device, memory);
    }

}