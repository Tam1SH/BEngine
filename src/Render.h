#pragma once
#include <vector>
#include <memory>
#include "AbstractRenderSystem.hpp"
namespace BEbraEngine {
    class RenderObject;
    class BaseVulkanRender;
    class GameObjectFactory;
    class Render {
    private:
        friend class GameObjectFactory;
        std::vector<std::weak_ptr<RenderObject>> RenderObjects;

        AbstractRender* render;
    public:
        Render(AbstractRender* render);

        void DrawFrame();

        void AddRenderObject(std::weak_ptr<RenderObject> object);

    };
}