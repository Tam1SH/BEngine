#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include "AbstractComponent.hpp"
#include "RenderObjectCreator.hpp"
#include "RenderBuffer.hpp"
//TODO: draw is bad bleat.
namespace BEbraEngine {
    class Mesh1;
    class Transform;
    class Texture;
    class RenderObject : public AbstractComponent {
    private:
        friend class RenderObjectFactory;

        static RenderObjectFactory* factory;

        static void SetFactory(RenderObjectFactory* factory);

        std::unique_ptr<Mesh1> MeshRenderer;

        std::shared_ptr<Transform> transform;

        std::unique_ptr<Texture> texture;

        std::shared_ptr<RenderBuffer> matBuffer;

        VkPipelineLayout* layout;

        VkDescriptorSet* descriptor;

        RenderObject();

    public:

        const RenderBuffer* getMatrixBuffer();

        static RenderObject* New(std::shared_ptr<Transform> transform);

        void Draw(VkCommandBuffer cmd);

        void Recreate();

        ~RenderObject();
    };
}
