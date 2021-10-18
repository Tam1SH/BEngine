#pragma once
#include <vulkan/vulkan.h>
#include "RenderBuffer.hpp"
namespace BEbraEngine {
    struct Buffer : public RenderBuffer{

        VkBuffer self = VK_NULL_HANDLE;

        VkDeviceMemory memory = VK_NULL_HANDLE;

        size_t size = 0;

        Buffer() { }
        Buffer(Buffer&& tmp) noexcept
            : self(tmp.self)
            , memory(tmp.memory)
            , size(tmp.size)
        {
            tmp.self = VK_NULL_HANDLE;
            tmp.memory = VK_NULL_HANDLE;
        }
        Buffer& operator=(Buffer&& tmp) noexcept;

        void Destroy();

        ~Buffer();
    };
}