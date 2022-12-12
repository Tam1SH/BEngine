
#include <vulkan.h>
#include "CommandBuffer.hpp"
#include <vector>
export module CommandPool;


namespace BEbraEngine {
    export class CommandPool {

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


