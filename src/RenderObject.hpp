#pragma once
#include "stdafx.h"
#include "AbstractComponent.hpp"
#include "RenderObjectCreator.hpp"
#include "RenderBuffer.hpp"
#include "IReusable.hpp"
#include "Model.hpp"
//TODO: draw is bad bleat.
namespace BEbraEngine {
    class Mesh1;
    class Transform;
    class Texture;
    class RenderObject : public GameObjectComponent, public IReusable {
    public:

        virtual ~RenderObject();
    public:

        std::unique_ptr<Mesh1> mesh;

        std::unique_ptr<Texture> texture;

        std::unique_ptr<Model> model;

        std::shared_ptr<RenderBufferView> matrix;

        RenderObject();
    };

    class VulkanRenderObject : public RenderObject {
    public:
        void release() override;

        void recreate();
    public:
        void Draw(VkCommandBuffer cmd);

        friend class VulkanRenderObjectFactory;

        static VulkanRenderObjectFactory* factory;

        static void SetFactory(VulkanRenderObjectFactory* factory);

        VkPipelineLayout* layout;

        VkDescriptorSet descriptor;
    };
}
