#include "stdafx.h"
#include "CommandPool.hpp"
#include "CommandBuffer.hpp"
#include "VulkanRender.hpp"
namespace BEbraEngine {
    void CommandPool::create(uint32_t queueFamilyIndex)
    {
        VkCommandPoolCreateInfo info{};
        info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        info.queueFamilyIndex = queueFamilyIndex;
        this->pool = 0;
        vkCreateCommandPool(VulkanRender::device, &info, 0, &pool);
    }
    CommandBuffer CommandPool::createCommandBuffer(CommandBuffer::Type type, VkCommandBufferUsageFlagBits bits)
    {
        CommandBuffer buffer = CommandBuffer();
        buffer.pool = this;
        buffer.type = type;
        buffer.usage = bits;
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = pool;
        if(type == CommandBuffer::Type::Primary)
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        if (type == CommandBuffer::Type::Secondary)
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
        allocInfo.commandBufferCount = 1;
        vkAllocateCommandBuffers(VulkanRender::device, &allocInfo, buffer.GetBuffer());
        countBuffers++;
        return buffer;

    }
    void CommandPool::destroyCmdBuffer(VkCommandBuffer buffer)
    {
        vkFreeCommandBuffers(VulkanRender::device, pool, 1, &buffer);
        countBuffers--;
    }
    void CommandPool::destroyCmdBuffers(std::vector<VkCommandBuffer> buffers)
    {
        vkFreeCommandBuffers(VulkanRender::device, pool, buffers.size(), buffers.data());
        countBuffers -= buffers.size();
    }


    CommandPool::~CommandPool()
    {
        vkDestroyCommandPool(VulkanRender::device, pool, 0);
    }

}

