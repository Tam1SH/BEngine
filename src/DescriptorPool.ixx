#include <vulkan.h>
#include <tbb.h>
export module DescriptorPool;
import <optional>;
import <list>;
import CreateInfoStructures;
import Debug;


namespace BEbraEngine {
    export class DescriptorPool final {

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

