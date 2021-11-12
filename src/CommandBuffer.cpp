#include "stdafx.h"
#include "CommandBuffer.hpp"
#include "VulkanRender.hpp"
namespace BEbraEngine {
    void CommandBuffer::Reset()
    {
        vkResetCommandBuffer(_buffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
    }


    void CommandBuffer::StartRecord(VkFramebuffer buffer)
    {
        VkCommandBufferInheritanceInfo InhInfo{};
        InhInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
        InhInfo.renderPass = renderPass;
        InhInfo.framebuffer = buffer;

        VkCommandBufferBeginInfo info{};
        info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
        if(type == CommandBuffer::Type::Secondary)
            info.pInheritanceInfo = &InhInfo;
        vkBeginCommandBuffer(_buffer, &info);

    }

    void CommandBuffer::EndRecord()
    {
        if (auto result = vkEndCommandBuffer(_buffer);
            result != VK_SUCCESS) {
        }
    }

}
