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

    class Light : public GameObjectComponent {
    public:
        struct ShaderData {
            alignas(16) Vector3 position;
            alignas(16) Vector3 color;
        };
    public:
        std::unique_ptr<Model> model;
        std::shared_ptr<RenderBufferView> data;
        Transform* transform;
        void setColor(const Vector3& color) {

            this->color = color;
        }
        void update() {
            ShaderData data1;
            data1.position = transform->GetPosition();
            data1.color = color;
            data->setData(&data1, sizeof(ShaderData));
        }
        Vector3& getColor() {
            return color;
        }
    private:
        Vector3 color;
    };
    class VulkanLight : public Light {
    public:
        void Draw(VkCommandBuffer cmd);

        VkPipelineLayout* layout;

        VkDescriptorSet LightSet;
    };
}
