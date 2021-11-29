#pragma once
#include <vulkan/vulkan.h>

namespace BEbraEngine {
    class CommandPool;
}
namespace BEbraEngine {
    class CommandBuffer {
    public:
        enum class Type {
            Primary,
            Secondary
        };
    public:
        CommandBuffer(){}
        CommandBuffer(CommandPool* pool, VkCommandBufferUsageFlagBits usage, CommandBuffer::Type type);

        operator VkCommandBuffer& () { return _buffer; }

        void reset();

        void startRecord(VkFramebuffer buffer = 0, VkRenderPass pass = 0);

        void endRecord();

        void destroy();

        VkCommandBuffer* GetBuffer() { return &_buffer; }

        void onCompleted(std::function<void()> callback) { this->callback = callback; }
    public:

        std::function<void()> callback;
        VkCommandBuffer _buffer;
        VkCommandBufferUsageFlagBits usage;
        CommandBuffer::Type type;
        CommandPool* pool;
    };
}