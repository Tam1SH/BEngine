#include "Render.h"
#include "RenderObject.h"
#include "BaseVulkanRender.hpp"
#include "VulkanRender.h"
//TODO: ты наху€ нужен?
namespace BEbraEngine {
    Render::Render(VulkanRender* render)
    {
        this->render = render;
    }

    void Render::DrawFrame()
    {
        render->UpdateFrame();
    }
    void Render::AddRenderObject(std::weak_ptr<RenderObject> object)
    {
        render->AddObject(object);
    }
}