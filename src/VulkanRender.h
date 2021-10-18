#pragma once
#include "BaseVulkanRender.hpp"
#include <list>
#include <chrono>


#include "Camera.hpp"
//TODO: крайне тупое решение.
namespace BEbraEngine {
    class RenderObject;
    class VulkanRender : public BaseVulkanRender {
    public:

        VkImageFormatProperties* imageFormatProperties;

        Camera* camera;

        int countOfObject = 200;

        std::list<std::weak_ptr<RenderObject>> objects;

        void SetDescriptorLayouts() override;

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

        void AddObject(std::weak_ptr<RenderObject> object);
    public:

        VulkanRender();

        ~VulkanRender() {
        }
    };
}