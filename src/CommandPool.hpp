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

        void Create(VkRenderPass renderPass);

        CommandBuffer createCommandBuffer(CommandBuffer::Type type);

        void DestroyCmdBuffer(VkCommandBuffer buffer);

        void DestroyCmdBuffers(std::vector<VkCommandBuffer> buffers);

        void Destroy();

        ~CommandPool();
    private:

        VkCommandPool pool;

        VkRenderPass renderPass;

        int countBuffers;
    };
}


