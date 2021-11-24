#pragma once
#include "stdafx.h"
#include "CreateInfoStructures.hpp"
#include <array>
#include "Debug.hpp"
#include <stdexcept>
//TODO: этот хуй может быть очень полезен, но в нЄм ниху€ нет.
namespace BEbraEngine {
    class DescriptorPool {

    public:

        operator VkDescriptorPool&() {
            return pool;
        }
        operator VkDescriptorPool* () {
            return &pool;
        }


        DescriptorPool(VulkanDescriptorPoolInfo info) { this->info = info; }
        ~DescriptorPool();

        void allocate(int count);

        void free(VkDescriptorSet set) {
            setsQueue.push(set);
        }
        std::optional<VkDescriptorSet> get() {
            VkDescriptorSet set;
            if (setsQueue.try_pop(set)) {
                return std::optional<VkDescriptorSet>(set);
                
            }
            return std::optional<VkDescriptorSet>();
        }

        VulkanDescriptorPoolInfo getInfo() { return info; }
    private:
        VulkanDescriptorPoolInfo info;
        VkDescriptorPool pool;
        tbb::concurrent_queue<VkDescriptorSet> setsQueue;
        int countDescriptors;

    };

}

