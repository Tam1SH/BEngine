#pragma once
#include "stdafx.h"
#include "AbstractComponent.hpp"
#include "RenderObjectCreator.hpp"
#include "RenderBuffer.hpp"
#include "IReusable.hpp"
//TODO: draw is bad bleat.
namespace BEbraEngine {
    class Mesh1;
    class Transform;
    class Texture;
    class RenderObject : public GameObjectComponent, public IReusable {
    public:

        void release() override;

        const RenderBuffer* getMatrixBuffer();

        static RenderObject* New(std::shared_ptr<Transform> transform);

        void Draw(VkCommandBuffer cmd);

        void Recreate();

        ~RenderObject();
    public:

        size_t offset;

        friend class VulkanRenderObjectFactory;

        static VulkanRenderObjectFactory* factory;

        static void SetFactory(VulkanRenderObjectFactory* factory);

        std::unique_ptr<Mesh1> MeshRenderer;

        std::shared_ptr<Transform> transform;

        std::unique_ptr<Texture> texture;

        std::shared_ptr<RenderBuffer> matBuffer;

        std::shared_ptr<RenderBufferView> _matBuffer;

        VkPipelineLayout* layout;

        VkDescriptorSet descriptor;

        VkDescriptorSet _descriptor;

        RenderObject();
    };
}
