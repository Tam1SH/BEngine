module;
#include <vulkan/vulkan.h>

export module VulkanBuffer;
import RenderBuffer;

namespace BEbraEngine {
    export struct VulkanBuffer : RenderBuffer {

        VkBuffer self = VK_NULL_HANDLE;
        VkDeviceMemory memory = VK_NULL_HANDLE;
        size_t size = 0;

        void destroy();

        ~VulkanBuffer();

        void setData(const void* data, uint32_t size, uint32_t offset);
    };
}