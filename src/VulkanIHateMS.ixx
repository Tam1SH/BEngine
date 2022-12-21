export module VulkanIHateMS;
import stdDeclaration;
import CommandPool;

namespace BEbraEngine {
    export struct LolCompileErrorXD {
        vector<unique_ptr<CommandPool>> concurrentCommandPools_RenderQueue;
        unique_ptr<CommandPool> swapChainRenderCommandPool;
        vector<unique_ptr<CommandPool>> concurrentCommandPools_TransferQueue;

    };

}