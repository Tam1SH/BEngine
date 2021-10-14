#pragma once
#ifdef __ANDROID__
#include <vulkan/vulkan.h>
#include "RenderWindow.hpp"
#include "BaseVulkanRender.hpp"
#include "platform.h"
#include "WorkSpace.h"
namespace BEbraEngine {
    
    class AbstractComponent;
    class DebugUI {
    private:
        friend class AbstractComponent;

        BaseVulkanRender* render;

        VulkanWindow* window;

        VkDescriptorPool imguiPool;

        std::shared_ptr<WorkSpace> workspace;

    private:
        static void check_vk_result(VkResult err);

        void _createPool();
    public:
        void UploadFonts();

        void Create(BaseVulkanRender* render, VulkanWindow* window);

        void SetWorkSpace(std::shared_ptr<WorkSpace> workspace);

        void TreeObjects(std::shared_ptr<AbstractComponent> component);

        void Prepare();

        void Destroy();

    };
}
#endif
