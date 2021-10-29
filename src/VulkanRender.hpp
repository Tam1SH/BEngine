#pragma once
#include "BaseVulkanRender.hpp"
#include <list>
#include <chrono>


#include "Camera.hpp"
//TODO: ������ ����� �������.
namespace BEbraEngine {
    class RenderObject;
    class VulkanRender : public BaseVulkanRender {
    public:

        VkImageFormatProperties* imageFormatProperties;

        Camera* camera;

        int countOfObject = 200;

        void Init() override;

        typedef std::chrono::high_resolution_clock Clock;
        std::chrono::time_point<std::chrono::steady_clock> t1;
        std::chrono::time_point<std::chrono::steady_clock> t2;

        void OnUpdateData() override;

        void StartRender();

        void EndRender();


        void OnDrawFrame() override;

        void OnCleanUp() override {

        }
        void OnRecreateSwapChain() override;

        void UpdateCamera();

    public:

        VulkanRender();

        ~VulkanRender() {
        }
    };
}