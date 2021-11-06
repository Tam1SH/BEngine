#pragma once
#include <vulkan/vulkan.h>
#include "VulkanRender.hpp"

namespace BEbraEngine {
    class CommandBuffer {
    public:
        enum BufferState {
            Invalid = 0,
            Initial = 1,
            Recording = 2,
            Executable = 3,
            Pending = 4 //TODO: Нужно же как-то ставить этот флаг
                        //Я ебу как это отслеживать внутри буфера?
                        //Pending задаётся при отправки в очередь жыпию(GPU)
        };



    public:

        static void SetRender(VulkanRender* render) {
            _render = render;
        }

        BufferState state;
        // operator VkCommandBuffer() { return buffer; }

        operator VkCommandBuffer& () { return buffer; }

        static void SetDevice(VkDevice device) {
            CommandBuffer::device = device;
        }

        BufferState GetState() {
            return state;
        }

        CommandBuffer() {}

        CommandBuffer(VkCommandPool pool, VkCommandBuffer buffer) : _pool(pool), buffer(buffer) {}

        CommandBuffer(const CommandBuffer& buffer) :
            buffer(buffer.buffer), _pool(buffer._pool) {
        }

        void SetPool(VkCommandPool pool) {
            _pool = pool;
        }
        void Reset() {
            vkResetCommandBuffer(buffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
        }

        void Create() {
            VkCommandBufferAllocateInfo info{};
            info.commandBufferCount = 1;
            info.commandPool = _pool;
            info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

            if (auto result = vkAllocateCommandBuffers(CommandBuffer::device, &info, &buffer);
                result != VK_SUCCESS) {
                state = Invalid;
            }
            state = Initial;
        }

        void Destroy() {
            if (_pool)
                vkFreeCommandBuffers(CommandBuffer::device, _pool, 1, &buffer);
        }

        void StartRecord() {
            VkCommandBufferInheritanceInfo InhInfo{};
            InhInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
            InhInfo.renderPass = _render->renderPass;

            VkCommandBufferBeginInfo info{};
            info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

            // info.pInheritanceInfo = &InhInfo;
            if (auto result = vkBeginCommandBuffer(*GetBuffer(), &info);
                result != VK_SUCCESS) {
                state = Invalid;
            }
            state = Recording;
        }

        void EndRecord() {
            if (auto result = vkEndCommandBuffer(buffer);
                result != VK_SUCCESS) {
                state = Invalid;
            }
            state = Executable;
        }

        VkCommandBuffer* GetBuffer() {
            return &buffer;
        }
        VkCommandPool GetPool() {
            return _pool;
        }
    private:

        inline static VulkanRender* _render;

        inline static VkDevice device;

        VkCommandBuffer buffer;

        VkCommandPool _pool;
    };
}