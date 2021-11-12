#pragma once
#include <vulkan/vulkan.h>
#include "VulkanRender.hpp"

namespace BEbraEngine {
    class CommandBuffer {
    public:
        enum class Type {
            Primary,
            Secondary
        };
    public:

        CommandBuffer() {}
        CommandBuffer(VkRenderPass renderPass, Type type) { this->renderPass = renderPass; }

        void Reset();

        void StartRecord(VkFramebuffer buffer = 0);

        void EndRecord();

        VkCommandBuffer* GetBuffer() { return &_buffer; }

    private:

        VkRenderPass renderPass;

        VkCommandBuffer _buffer;

        Type type;
    };
}