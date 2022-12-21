#include <vulkan.h>
#include <tbb.h>
#include <optional>
#include <mutex>
#include <memory>
#include <list>
export module DescriptorPool;


namespace BEbraEngine {
    export class VulkanDescriptorPoolInfo;
}

namespace BEbraEngine {

    export class DescriptorPool final {

    public:

        operator VkDescriptorPool&() {
            return pool;
        }
        operator VkDescriptorPool* () {
            return &pool;
        }

        DescriptorPool(VulkanDescriptorPoolInfo& info);
       
        ~DescriptorPool();

        void allocate(uint32_t count);

        void free(VkDescriptorSet set);

        std::optional<VkDescriptorSet> get();

        VulkanDescriptorPoolInfo& getInfo();

        DescriptorPool(const DescriptorPool& o) = delete;
        DescriptorPool& operator=(const DescriptorPool& o) = delete;

    private:
        std::unique_ptr<VulkanDescriptorPoolInfo> info;
        VkDescriptorSetLayout layout{};
        VkDescriptorPool pool{};

        tbb::concurrent_queue<VkDescriptorSet> sets;
        
        std::list<VkDescriptorSet> setsUses;
        std::mutex mutex;

        uint32_t countDescriptors{ 0 };

    };

}

