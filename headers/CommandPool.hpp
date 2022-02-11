#pragma once
#include "stdafx.h"
#include "CommandBuffer.hpp"
#include "platform.hpp"
using BE_STD::vector;

//TODO: этот хуй бесполезен, ну почти.
namespace BEbraEngine {
    class CommandPool final {

    public:

        operator VkCommandPool() {
            return pool;
        }

        CommandPool() {}

        void create(uint32_t queueFamilyIndex);

        CommandBuffer createCommandBuffer(CommandBuffer::Type type, VkCommandBufferUsageFlagBits bits);

        void destroyCmdBuffer(VkCommandBuffer buffer);

        void destroyCmdBuffers(vector<VkCommandBuffer> buffers);

        ~CommandPool();
    private:

        VkCommandPool pool{};

        size_t countBuffers{};
    };
}


