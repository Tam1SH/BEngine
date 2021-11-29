#pragma once
#include "stdafx.h"
#include "CommandBuffer.hpp"


//TODO: этот хуй бесполезен, ну почти.
namespace BEbraEngine {
    class CommandPool {

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

        VkCommandPool pool;

        int countBuffers;
    };
}


