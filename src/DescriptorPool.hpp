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

        void free(VkDescriptorSet set);
        std::optional<VkDescriptorSet> get();

        VulkanDescriptorPoolInfo getInfo() { return info; }
    private:
        VulkanDescriptorPoolInfo info;
        VkDescriptorSetLayout layout;
        VkDescriptorPool pool;

        tbb::concurrent_queue<VkDescriptorSet> sets;
        //производительно нахуй? не то слово бл€ть
        std::list<VkDescriptorSet> setsUses;
        std::mutex mutex;

        int countDescriptors;

    };

}

