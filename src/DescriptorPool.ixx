#include <vulkan.h>

export module DescriptorPool;
import <optional>;
import <tbb.h>;
import <list>;
import <mutex>;
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

        DescriptorPool(const DescriptorPool& o) = delete;
        DescriptorPool& operator=(const DescriptorPool& o) = delete;
        //TODO: �������������� move �����������

       //. DescriptorPool() noexcept {}
        //~DescriptorPool() noexcept;

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

