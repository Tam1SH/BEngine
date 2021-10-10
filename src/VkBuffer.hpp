#pragma once
#include <vulkan/vulkan.h>
#include <iostream>
namespace BEbraEngine {
    struct Buffer {

        VkBuffer self = VK_NULL_HANDLE;

        VkDeviceMemory memory = VK_NULL_HANDLE;

        size_t size = 0;

        Buffer() {
        }
        Buffer(Buffer&& tmp) noexcept
            : self(tmp.self)
            , memory(tmp.memory)
            , size(tmp.size)
        {
            tmp.self = VK_NULL_HANDLE;
            tmp.memory = VK_NULL_HANDLE;
        }
        Buffer& operator=(Buffer&& tmp) noexcept
        {
            Destroy();
            size = tmp.size;
            self = tmp.self;
            memory = tmp.memory;
            tmp.memory = VK_NULL_HANDLE;
            tmp.self = VK_NULL_HANDLE;
            return *this;
        }
        void Destroy();

        ~Buffer();
    };
}