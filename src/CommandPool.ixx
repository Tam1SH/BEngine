
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

        CommandPool() {}

        void create(uint32_t queueFamilyIndex);

        CommandBuffer createCommandBuffer(CommandBuffer::Type type, VkCommandBufferUsageFlagBits bits);

        void destroyCmdBuffer(VkCommandBuffer buffer);

        void destroyCmdBuffers(std::vector<VkCommandBuffer> buffers);

        ~CommandPool();
    private:

        VkCommandPool pool{};

        size_t countBuffers{};
    };
}


