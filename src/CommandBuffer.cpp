#include <vulkan.h>
module CommandBuffer;
import CommandPool;
namespace BEbraEngine {
    CommandBuffer::CommandBuffer(CommandPool* pool, VkCommandBufferUsageFlagBits usage, CommandBuffer::Type type) noexcept
    {
        this->pool = pool;
        this->usage = usage;
        this->type = type;
    }
    void CommandBuffer::reset()
    {
        vkResetCommandBuffer(_buffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
    }


    void CommandBuffer::startRecord(VkFramebuffer buffer, VkRenderPass pass)
    {
        VkCommandBufferInheritanceInfo InhInfo{};
        InhInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
        InhInfo.renderPass = pass;
        InhInfo.framebuffer = buffer;

        VkCommandBufferBeginInfo info{};
        info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        info.flags = usage;
        if(type == CommandBuffer::Type::Secondary)
            info.pInheritanceInfo = &InhInfo;
        vkBeginCommandBuffer(_buffer, &info);

    }

    void CommandBuffer::endRecord()
    {
        if (auto result = vkEndCommandBuffer(_buffer);
            result != VK_SUCCESS) {
        }
    }

    void CommandBuffer::destroy()
    {
        if(_callback)
            _callback();
        pool->destroyCmdBuffer(*this);
    }

}
