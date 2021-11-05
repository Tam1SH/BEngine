#include "stdafx.h"
#include "VulkanRender.hpp"

#include "DescriptorPool.hpp"
namespace BEbraEngine {
    DescriptorPool::~DescriptorPool()
    {
        vkDestroyDescriptorPool(VulkanRender::device, pool, 0);
    }
    void DescriptorPool::allocate(int count)
    {
        countDescriptors = count;

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = info.types.size();
        poolInfo.pPoolSizes = info.types.data();
        poolInfo.maxSets = static_cast<uint32_t>(countDescriptors);
        VkResult result;
        if (result = vkCreateDescriptorPool(VulkanRender::device, &poolInfo, nullptr, &pool); result != VK_SUCCESS) {
            Debug::Log("Failed to create decsriptor pool");
        }
    }
}