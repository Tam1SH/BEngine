
//TODO: imgui ���� ����� ����� � ����� �������, �� ���� ���������� �� ��������� ����������� ���(������� ��������) �����.
#ifdef __ANDROID__1
#pragma once
#include "stdafx.h"
#include "RenderWindow.hpp"
#include "BaseVulkanRender.hpp"
#include "platform.h"
#include "WorkSpace.h"
namespace BEbraEngine {
    
    class AbstractComponent;
    class DebugUI {
    private:
        friend class AbstractComponent;

        VulkanRender* render;

        VulkanWindow* window;

        VkDescriptorPool imguiPool;

        std::shared_ptr<WorkSpace> workspace;

    private:
        static void check_vk_result(VkResult err);

        void _createPool();
    public:
        void UploadFonts();

        void Create(VulkanRender* render, VulkanWindow* window);

        void SetWorkSpace(std::shared_ptr<WorkSpace> workspace);

        void TreeObjects(std::shared_ptr<AbstractComponent> component);

        void Prepare();

        void destroyObject();

    };
}
#endif
