#pragma once
#include <vector>
#include <memory>
namespace BEbraEngine {
    class RenderObject;
    class BaseVulkanRender;
    class GameObjectFactory;
    class VulkanRender;
    class Render {
    private:
        friend class GameObjectFactory;
        std::vector<std::weak_ptr<RenderObject>> RenderObjects;

        VulkanRender* render;
    public:
        Render(VulkanRender* render);

        void DrawFrame();

        void AddRenderObject(std::weak_ptr<RenderObject> object);

    };
}