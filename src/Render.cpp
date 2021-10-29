#include "stdafx.h"
#include "Render.hpp"
#include "RenderObject.hpp"
#include "BaseVulkanRender.hpp"
#include "VulkanRender.hpp"
//TODO: ты наху€ нужен?
namespace BEbraEngine {
    Render::Render(AbstractRender* render)
    {
        this->render = static_cast<VulkanRender*>(render);
    }

    void Render::DrawFrame()
    {
        static_cast<VulkanRender*>(render)->UpdateFrame();
    }
    void Render::AddRenderObject(std::weak_ptr<RenderObject> object)
    {
        static_cast<VulkanRender*>(render)->AddObject(object);
    }
}