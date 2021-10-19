#include "VkBuffer.hpp"
#include "BaseVulkanRender.hpp"
//TODO: сделать не зависимым от граф. апи.
namespace BEbraEngine {

    void Buffer::Destroy()
    {
        vkFreeMemory(BaseVulkanRender::device, memory, 0);
        vkDestroyBuffer(BaseVulkanRender::device, self, 0);
        memory = 0;
        self = 0;
    }

    Buffer::~Buffer()
    {
        if (memory || self) {
            vkFreeMemory(BaseVulkanRender::device, memory, 0);
            vkDestroyBuffer(BaseVulkanRender::device, self, 0);
        }

    }
    void Buffer::setData(void* data, size_t size, size_t offset)
    {
        void* _data;
        vkMapMemory(BaseVulkanRender::device, memory, 0, size, 0, &_data);
        memcpy(_data, data, size);
        vkUnmapMemory(BaseVulkanRender::device, memory);
       /*
               void* _data;
        vkMapMemory(BaseVulkanRender::device, memory, 0, sizeof(glm::mat4), 0, &_data);
        memcpy(_data, &model, sizeof(glm::mat4));
        vkUnmapMemory(BaseVulkanRender::device, memory);
       */
    }
}