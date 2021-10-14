#include "VkBuffer.hpp"
#include "BaseVulkanRender.hpp"
namespace BEbraEngine {
    Buffer& Buffer::operator=(Buffer&& tmp) noexcept
    {
        Destroy();
        size = tmp.size;
        self = tmp.self;
        memory = tmp.memory;
        tmp.memory = VK_NULL_HANDLE;
        tmp.self = VK_NULL_HANDLE;
        return *this;
    }
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
}