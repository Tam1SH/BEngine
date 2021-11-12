#include "stdafx.h"
#include "CommandPool.hpp"
#include "VulkanRender.hpp"
namespace BEbraEngine {
    void CommandPool::Create(VkRenderPass renderPass)
    {
        this->renderPass = renderPass;
        VkCommandPoolCreateInfo info{};
        info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        info.queueFamilyIndex = VulkanRender::FamilyIndices.graphicsFamily.value();
        vkCreateCommandPool(VulkanRender::device, &info, 0, &pool);
    }
    CommandBuffer CommandPool::createCommandBuffer(CommandBuffer::Type type)
    {
        CommandBuffer buffer{ renderPass, type };
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = pool;
        if(type == CommandBuffer::Type::Primary)
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        if (type == CommandBuffer::Type::Secondary)
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
        allocInfo.commandBufferCount = 1;
        vkAllocateCommandBuffers(VulkanRender::device, &allocInfo, buffer.GetBuffer());
        countBuffers += 1;
        return buffer;

    }
    void CommandPool::DestroyCmdBuffer(VkCommandBuffer buffer)
    {
        vkFreeCommandBuffers(VulkanRender::device, pool, 1, &buffer);
        countBuffers--;
    }
    void CommandPool::DestroyCmdBuffers(std::vector<VkCommandBuffer> buffers)
    {
        vkFreeCommandBuffers(VulkanRender::device, pool, buffers.size(), buffers.data());
        countBuffers -= buffers.size();
    }

    void CommandPool::Destroy()
    {
        vkDestroyCommandPool(VulkanRender::device, pool, 0);
        pool = 0;
    }

    CommandPool::~CommandPool()
    {
        if(pool)
            vkDestroyCommandPool(VulkanRender::device, pool, 0);
    }

}

