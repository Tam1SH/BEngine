#pragma once
#include <vulkan/vulkan.h>
#include <array>
#include "BaseVulkanRender.hpp"
#include <stdexcept>
namespace BEbraEngine {
    class DescriptorPool {
    private:
        VkDescriptorPool pool;

        int countDescriptors;

    public:

        operator VkDescriptorPool() {
            return pool;
        }


        DescriptorPool() {}

        void Create() {
            countDescriptors = 1;
            std::array<VkDescriptorPoolSize, 3> poolSizes{};
            poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            poolSizes[0].descriptorCount = static_cast<uint32_t>(countDescriptors);
            poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            poolSizes[1].descriptorCount = static_cast<uint32_t>(countDescriptors);
            poolSizes[2].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            poolSizes[2].descriptorCount = static_cast<uint32_t>(countDescriptors);

            VkDescriptorPoolCreateInfo poolInfo{};
            poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
            poolInfo.poolSizeCount = poolSizes.size();
            poolInfo.pPoolSizes = poolSizes.data();
            poolInfo.maxSets = static_cast<uint32_t>(countDescriptors);

            if (vkCreateDescriptorPool(BaseVulkanRender::device, &poolInfo, nullptr, &pool) != VK_SUCCESS) {
                throw std::runtime_error("failed to create descriptor pool!");
            }
        }

    };
}

