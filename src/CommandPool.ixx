
#include "platform.hpp"
#include <vulkan.h>
export module CommandPool;
import CommandBuffer;

import <vector>;


namespace BEbraEngine {
    export class CommandPool final {

    public:

        operator VkCommandPool() {
            return pool;
        }

        

        void create(uint32_t queueFamilyIndex);

        CommandBuffer createCommandBuffer(CommandBuffer::Type type, VkCommandBufferUsageFlagBits bits);

        void destroyCmdBuffer(VkCommandBuffer buffer);

        void destroyCmdBuffers(std::vector<VkCommandBuffer> buffers);

        CommandPool(const CommandPool& o) = delete;
        CommandPool& operator=(const CommandPool& o) = delete;
        //TODO: �������������� move �����������

        CommandPool() noexcept {}
        ~CommandPool() noexcept;
    private:

        VkCommandPool pool{};

        size_t countBuffers{};
    };
}


