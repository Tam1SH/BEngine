#pragma once
#include "stdafx.h"
#include "AbstractComponent.hpp"
#include "RenderBuffer.hpp"
#include "IReusable.hpp"
#include "Model.hpp"
#include "matrix.hpp"
namespace BEbraEngine {
    class Transform;
    class Texture;
}

//TODO: draw is bad bleat.
namespace BEbraEngine {

    class RenderObject : public GameObjectComponent, public IReusable {
    public:
        struct ShaderData {
            Matrix4 model;
            alignas(16) Vector3 color;
        };

    public:

        std::unique_ptr<Texture> texture;

        std::shared_ptr<Model> model;

        std::shared_ptr<RenderBufferView> matrix;

        std::shared_ptr<Transform> transform;

        void update();

        virtual ~RenderObject();

        RenderObject();

        void setColor(const Vector3& color) {

            _color = color;
        }
        Vector3& getColor() {
            return _color;
        }
    private:
        Vector3 _color;
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


    class DirectionLight : public GameObjectComponent {
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
            _direction = direction;
        }
        void update() {
            ShaderData data1;
            if (!data.expired()) {
                data1.direction = _direction;
                data1.ambient = color;
                data1.diffuse = color;
                data1.specular = color;
                data.lock()->setData(&data1, sizeof(ShaderData));
            }
            else
                Debug::log(getName() + " has invalid data");

        }
        Vector3& getDirection() {
            return _direction;
        }
        Vector3& getColor() {
            return color;
        }

        DirectionLight() { name = "DirectionLight"; }
        virtual ~DirectionLight() {}

    private:
        Vector3 color;
        Vector3 _direction;
    };

}
