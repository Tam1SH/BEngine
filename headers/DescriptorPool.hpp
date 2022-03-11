#pragma once
#include "stdafx.h"
#include "CreateInfoStructures.hpp"
#include "Debug.hpp"
#include <stdexcept>

namespace BEbraEngine {
    class DescriptorPool final {

    public:

        operator VkDescriptorPool&() {
            return pool;
        }
        operator VkDescriptorPool* () {
            return &pool;
        }


        DescriptorPool(VulkanDescriptorPoolInfo info) { this->info = info; }
        ~DescriptorPool();

        void allocate(uint32_t count);

        void free(VkDescriptorSet set);

        std::optional<VkDescriptorSet> get();

        VulkanDescriptorPoolInfo getInfo() { return info; }
    private:
        VulkanDescriptorPoolInfo info{};
        VkDescriptorSetLayout layout{};
        VkDescriptorPool pool{};

        tbb::concurrent_queue<VkDescriptorSet> sets;
        

        std::list<VkDescriptorSet> setsUses;
        std::mutex mutex;

        uint32_t countDescriptors{ 0 };

    };

}

