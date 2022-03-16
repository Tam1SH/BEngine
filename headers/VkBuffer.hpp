#pragma once
#include <vulkan/vulkan.h>
#include "RenderBuffer.hpp"
namespace BEbraEngine {
    class VulkanBuffer : public RenderBuffer {
    public:
        VkBuffer self = VK_NULL_HANDLE;
        VkDeviceMemory memory = VK_NULL_HANDLE;
        size_t size = 0;

        void destroy() override;
        void setData(const void* data, uint32_t size, uint32_t offset) override;

        VulkanBuffer() { }
        ~VulkanBuffer();
    };
}