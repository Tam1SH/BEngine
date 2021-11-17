#pragma once
#include "stdafx.h"
#include "AbstractComponent.hpp"
#include "RenderBuffer.hpp"
#include "IReusable.hpp"
#include "Model.hpp"
#include "matrix.hpp"
namespace BEbraEngine {
    class VulkanRenderObjectFactory;
}

//TODO: draw is bad bleat.
namespace BEbraEngine {
    class Transform;
    class Texture;
    class RenderObject : public GameObjectComponent, public IReusable {
    public:
        struct ShaderData {
            Matrix4 model;
            alignas(16) Vector3 color;
        };
    public:

        virtual ~RenderObject() {}
    public:
        //TODO: useless;
        std::unique_ptr<Texture> texture;

        std::shared_ptr<Model> model;

        std::weak_ptr<RenderBufferView> matrix;

        std::weak_ptr<Transform> transform;

        void update();

        RenderObject() {}

        void setColor(const Vector3& color) {

            this->color = color;
        }
        Vector3& getColor() {
            return color;
        }
    private:
        Vector3 color;
    };

    class VulkanRenderObject : public RenderObject {
    public:
        void release() override;

        ~VulkanRenderObject() {}
    public:
        void Draw(VkCommandBuffer cmd);

        VkPipelineLayout* layout;

        VkDescriptorSet descriptor;
    };


    class PointLight : public GameObjectComponent, public IReusable {
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
        std::weak_ptr<RenderBufferView> data;

        std::weak_ptr<Transform> transform;

        void release() override;

        void setColor(const Vector3& color) {

            this->color = color;
        }
        Vector3& getColor() {
            return color;
        }
        void update();


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
        std::weak_ptr<RenderBufferView> data;

        void setColor(const Vector3& color) {

            this->color = color;
        }
        void setDirection(const Vector3& direction) {
            this->direction = direction;
        }
        void update() {
            ShaderData data1;
            if (!data.expired()) {
                data1.direction = direction;
                data1.ambient = color;
                data1.diffuse = color;
                data1.specular = color;
                data.lock()->setData(&data1, sizeof(ShaderData));
            }
            else
                Debug::Log(GetName() + " has invalid data");

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

        VkDescriptorSet descriptor;
    };

    class VulkanDirLight : public DirLight {
    public:

        VkDescriptorSet descriptor;
        ~VulkanDirLight() {}
    };
}
