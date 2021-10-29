#pragma once
#include "stdafx.h"
#include "AbstractRenderSystem.hpp"
namespace BEbraEngine {
    class RenderObject;
    class BaseVulkanRender;
    class GameObjectFactory;
    class Render {
    public:
        Render(AbstractRender* render);

        void DrawFrame();

        void AddRenderObject(std::weak_ptr<RenderObject> object);

    private:
        friend class GameObjectFactory;
        std::vector<std::weak_ptr<RenderObject>> RenderObjects;

        AbstractRender* render;
    };
}