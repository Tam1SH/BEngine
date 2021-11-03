#pragma once
#include <vulkan/vulkan.h>
#include "RenderBuffer.hpp"
namespace BEbraEngine {
    struct VulkanBuffer : public RenderBuffer {
        VkBuffer self = VK_NULL_HANDLE;
        VkDeviceMemory memory = VK_NULL_HANDLE;
        size_t size = 0;

        void Destroy() override;
        void setData(void* data, size_t size, size_t offset) override;
        VulkanBuffer() { }
        ~VulkanBuffer();
    };
}