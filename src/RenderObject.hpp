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
        struct ShaderData {
            Matrix4 model;
            alignas(16) Vector3 color;
        };
    public:

        virtual ~RenderObject();
    public:

        std::unique_ptr<Texture> texture;

        std::shared_ptr<Model> model;

        std::shared_ptr<RenderBufferView> matrix;
        void setColor(const Vector3& color) {
            auto color_ = color;
            matrix->setData(&color_, sizeof(Vector4), sizeof(Matrix4));
        }
        RenderObject();
    private:
    };

    class VulkanRenderObject : public RenderObject {
    public:
        void release() override;

        void recreate();

        ~VulkanRenderObject();
    public:
        void Draw(VkCommandBuffer cmd);

        friend class VulkanRenderObjectFactory;

        static VulkanRenderObjectFactory* factory;

        static void SetFactory(VulkanRenderObjectFactory* factory);

        VkPipelineLayout* layout;

        VkDescriptorSet descriptor;
    };


    class PointLight : public GameObjectComponent {
    public:
        struct ShaderData {
            alignas(16) Vector3 position;

            //компоненты света
            alignas(16) Vector3 ambient;
            alignas(16) Vector3 diffuse;
            alignas(16) Vector3 specular;

            alignas(4) float constant;
            alignas(4) float linear;
            alignas(4) float quadratic;
        };
    public:
        std::shared_ptr<RenderBufferView> data;

        Transform* transform;

        void setColor(const Vector3& color) {

            this->color = color;
        }

        void update() {
            ShaderData data1;
            data1.position = transform->GetPosition();
            data1.ambient = color;
            data1.diffuse = color;
            data1.specular = color;
            data1.constant = 1.f;
            data1.linear = 0.35f;
            data1.quadratic = 1.8f;
            data->setData(&data1, sizeof(ShaderData));
        }
        Vector3& getColor() {
            return color;
        }
        PointLight() { name = "Light"; }
        virtual ~PointLight() {}
    private:
        Vector3 color;
    };


    class DirLight : public GameObjectComponent {
    public:
        struct ShaderData {
            alignas(16) Vector3 direction;

            //компоненты света
            alignas(16) Vector3 ambient;
            alignas(16) Vector3 diffuse;
            alignas(16) Vector3 specular;

        };



    public:
        std::shared_ptr<RenderBufferView> data;

        Transform* transform;
        void setColor(const Vector3& color) {

            this->color = color;
        }
        void setDirection(const Vector3& direction) {
            this->direction = direction;
        }
        void update() {
            ShaderData data1;
            data1.direction = direction;
            data1.ambient = color;
            data1.diffuse = color;
            data1.specular = color;
            data->setData(&data1, sizeof(ShaderData));
        }
        Vector3& getDirection() {
            return direction;
        }
        Vector3& getColor() {
            return color;
        }
        DirLight() { name = "DirectionLight"; }
        virtual ~DirLight() {}

    private:
        Vector3 color;
        Vector3 direction;
    };

    class VulkanLight : public PointLight {
    public:
        VkPipelineLayout* layout;

        VkDescriptorSet descriptor;
    };

    class VulkanDirLight : public DirLight {
    public:
        VkPipelineLayout* layout;

        VkDescriptorSet descriptor;
        ~VulkanDirLight() {}
    };
}
