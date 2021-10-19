#include "Render.h"
#include "RenderObject.h"
#include "BaseVulkanRender.hpp"
#include "VulkanRender.h"
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