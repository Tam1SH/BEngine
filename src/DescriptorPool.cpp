#include "stdafx.h"
#include "VulkanRender.hpp"

#include "DescriptorPool.hpp"
namespace BEbraEngine {
    DescriptorPool::~DescriptorPool()
    {
        vkDestroyDescriptorPool(VulkanRender::device, pool, 0);
    }
    void DescriptorPool::allocate(uint32_t count)
    {
        countDescriptors += count;

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<uint32_t>(info.types.size());
        poolInfo.pPoolSizes = info.types.data();
        poolInfo.maxSets = countDescriptors;
        VkResult result;

        if (result = vkCreateDescriptorPool(VulkanRender::device, &poolInfo, nullptr, &pool); result != VK_SUCCESS) {
            DEBUG_LOG2("Failed to create decsriptor pool", this, "DescriptorPool", Debug::ObjectType::DescriptorPool, Debug::MessageType::Error);
            return;
        }

        for (uint32_t i = 0; i < countDescriptors; i++) {
            auto set = VkDescriptorSet();
            VkDescriptorSetAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
            allocInfo.descriptorPool = pool;
            allocInfo.descriptorSetCount = 1;
            allocInfo.pSetLayouts = &info.layout;
            VkResult res;
            res = vkAllocateDescriptorSets(VulkanRender::device, &allocInfo, &set);
            sets.push(set);
        }
    }
    void DescriptorPool::free(VkDescriptorSet set)
    {

        {
            std::lock_guard g(mutex);
            std::remove(setsUses.begin(), setsUses.end(), set);
        }
        sets.push(set);
    }
    std::optional<VkDescriptorSet> DescriptorPool::get()
    {
        VkDescriptorSet set;


        if (sets.try_pop(set)) {
            setsUses.push_front(set);

            
            return std::optional<VkDescriptorSet>(set);
        }
        else
            DEBUG_LOG1("sets is empty");

        return std::optional<VkDescriptorSet>();
    }
}