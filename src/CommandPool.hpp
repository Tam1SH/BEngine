#pragma once
#include <vulkan.h>
#include <array>
#include <vector>
//TODO: этот хуй бесполезен, ну почти.
class CommandPool {
private:

    static VkDevice device;

    VkCommandPool pool;

    int countBuffers;

public:
    static void SetDevice(VkDevice device) {
        CommandPool::device = device;
    }

    operator VkCommandPool() {
        return pool;
    }

    CommandPool() {}

    void Create() {}

    VkCommandBuffer createCmdBuffer() {
        VkCommandBuffer buffer;
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = pool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;
        countBuffers += 1;
        auto result = vkAllocateCommandBuffers(device, &allocInfo, &buffer);
        return buffer;

    }

    void DestroyCmdBuffer(VkCommandBuffer buffer) {
        vkFreeCommandBuffers(device, pool, 1, &buffer);
        countBuffers--;
    }

    template<int Size>
    void DestroyCmdBuffers(std::array<VkCommandBuffer, Size> buffers) {
        vkFreeCommandBuffers(device, pool, Size, buffers.data());
        countBuffers -= buffers.size();
    }

    void DestroyCmdBuffers(std::vector<VkCommandBuffer> buffers) {
        vkFreeCommandBuffers(device, pool, buffers.size(), buffers.data());
        countBuffers -= buffers.size();
    }


    void Destroy() {
        vkDestroyCommandPool(device, pool, 0);
    }

    ~CommandPool() {
        vkDestroyCommandPool(device, pool, 0);
    }
};

