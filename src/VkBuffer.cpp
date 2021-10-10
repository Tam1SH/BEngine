#include "VkBuffer.hpp"
#include "BaseVulkanRender.hpp"
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
            std::cout << "DESTROY BUFFER  " << this << std::endl;
            vkFreeMemory(BaseVulkanRender::device, memory, 0);
            vkDestroyBuffer(BaseVulkanRender::device, self, 0);
        }

    }
}