
#include <vulkan/vulkan.h>
#include "platform.hpp"


export module CommandBuffer;
import <functional>;

namespace BEbraEngine {
    export class CommandPool;
}

namespace BEbraEngine {

    export class CommandBuffer final {
    public:
        friend class CommandPool;

        enum class Type {
            Primary,
            Secondary
        };
    public:


        operator VkCommandBuffer& () { return _buffer; }

        void reset();

        void startRecord(VkFramebuffer buffer = 0, VkRenderPass pass = 0);

        void endRecord();

        void destroy();

        VkCommandBuffer* GetBuffer() { return &_buffer; }

        void onCompleted(std::function<void()> callback) { _callback = callback; }

        //CommandBuffer(const CommandBuffer& o) = delete;
        //CommandBuffer& operator=(const CommandBuffer& o) = delete;
        //TODO: �������������� move �����������

        CommandBuffer() noexcept {}
        CommandBuffer(CommandPool* pool, VkCommandBufferUsageFlagBits usage, CommandBuffer::Type type) noexcept;
        ~CommandBuffer() noexcept {}

    private:

        std::function<void()> _callback{};
        VkCommandBuffer _buffer{};
        VkCommandBufferUsageFlagBits usage{};
        CommandBuffer::Type type{};
        CommandPool* pool{};
    };
}