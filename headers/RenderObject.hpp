#pragma once
#include "stdafx.h"
#include "platform.hpp"
#include "GameComponent.hpp"
#include "RenderBuffer.hpp"
#include "IReusable.hpp"
#include "Model.hpp"
#include "matrix.hpp"
#include "Debug.hpp"
#include "AbstractRender.hpp"
#include "IRenderData.hpp"
namespace BEbraEngine {
    class Transform;
    class Texture;
}

using BE_STD::weak_ptr;
using BE_STD::unique_ptr;
//TODO: draw is bad bleat.
namespace BEbraEngine {

    class Line : public IRenderData {
    public:
        struct ShaderData {
            alignas(16) Vector3 from;
            alignas(16) Vector3 to;
            alignas(16) Vector3 color;
        };
    public:
        ShaderData _data;

        Line(const Vector3& from = Vector3(0), const Vector3& to = Vector3(0), const Vector3& color = Vector3(0)) :
            from(from), to(to), color(color) { }
        ~Line();

        const void* getData() noexcept override {

            _data.color = color;
            _data.from = from;
            _data.to = to;
            return &data;
        }
        size_t getDataSize() const noexcept override {
            return sizeof(ShaderData);
        }

        Vector3 from;
        Vector3 to;
        Vector3 color;

        void create(AbstractRender& render);

        void update();

        shared_ptr<RenderBufferView> data;
        shared_ptr<RenderBuffer> vertices;
        shared_ptr<Transform> transform;
    };

    class Light : public GameComponent, public IReusable {
    public:
        struct ShaderData {
            alignas(16) Vector3 position;

            alignas(16) Vector3 color;
            alignas(16) Vector3 diffuse;
            alignas(16) Vector3 specular;

            alignas(4) float constant;
            alignas(4) float linear;
            alignas(4) float quadratic;
        };
        
        struct CreateInfo {
            const Vector3 lightColor{ 1 };
            float constant{};
            float linear{};
            float quadratic{};
        };
    public:

        void destroy(IVisitorGameComponentDestroyer& destroyer) override;

        shared_ptr<RenderBufferView> data;

        Transform* transform;

        void release() override;

        void setColor(const Vector3& color) {

            this->color = color;
        }
        Vector3& getColor() {
            return color;
        }
        void update();


        Light() { name_ = "Light"; }
        virtual ~Light() {}
    private:
        Vector3 color;

    };


    class DirectionLight : public GameComponent {
    public:
        struct ShaderData {
            alignas(16) Vector3 direction;

            alignas(16) Vector3 color;
            alignas(16) Vector3 diffuse;
            alignas(16) Vector3 specular;

        };
        struct CreateInfo {
            const Vector3 lightColor{ 1 };
        };


    public:
        shared_ptr<RenderBufferView> data;

        void setColor(const Vector3& color) {

            this->color = color;
        }
        void setDirection(const Vector3& direction) {
            _direction = direction;
        }
        void update() {
            ShaderData data1;
            data1.direction = _direction;
            data1.color = color;
            data1.diffuse = color;
            data1.specular = color;
            data->setData(&data1, sizeof(ShaderData));
        }
        Vector3& getDirection() {
            return _direction;
        }
        Vector3& getColor() {
            return color;
        }

        DirectionLight() { name_ = "DirectionLight"; }
        virtual ~DirectionLight() {}


        virtual void destroy(IVisitorGameComponentDestroyer& destroyer) override;
    private:
        Vector3 color;
        Vector3 _direction;


    };

    class Material : public GameComponent {
        DEBUG_DESTROY_CHECK_DECL()
    public:
        friend class GameComponentDestroyer;
        struct CreateInfo {
            boost::filesystem::path color;
            boost::filesystem::path specular;
            boost::filesystem::path normal;
        };
    public:
        Material(shared_ptr<Texture> color);
        Material(Texture* color,
            Texture* specular,
            Texture* normal);

        virtual void destroy(IVisitorGameComponentDestroyer& destroyer) override;

        ~Material();

        Texture& getColor() { return *color; }
        Texture& getSpecular() { return *specular; }
        Texture& getNormal() { return *normal; }

        shared_ptr<Texture> color;
        shared_ptr<Texture> specular;
        shared_ptr<Texture> normal;

    };

    class RenderObject : public GameComponent, public IReusable {
        DEBUG_DESTROY_CHECK_DECL()
    public:
        struct ShaderData {
            Matrix4 model;
            alignas(16) Vector3 color;
            int hasMaps{false};
        };

        struct CreateInfo {

            const Light::CreateInfo* pointLightInfo;
            const DirectionLight::CreateInfo* directionLightInfo;
        };
    public:


        void destroy(IVisitorGameComponentDestroyer& destroyer) override;

        Material* material;

        shared_ptr<Model> model;

        shared_ptr<RenderBufferView> matrix;

        Transform* transform;

        void update();

        virtual ~RenderObject();

        RenderObject();

        void setColor(const Vector3& color) {

            _color = color;
        }
        Vector3& getColor() {
            return _color;
        }
        bool hasMaps;
    private:
        Vector3 _color;

        // Унаследовано через IReusable
        virtual void release() override;
    };


}
