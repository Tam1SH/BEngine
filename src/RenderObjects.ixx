#include "platform.hpp"
#include <boost/filesystem.hpp>

export module RenderObjects;
import Model;
import <memory>;
import RenderBuffer;
import Matrix4;
import GameComponent;
import Vector3;
import Texture;
import Transform;

//import ÑVisitorComponentDestroyer;

namespace BEbraEngine {

    class Texture;
    class VisitorGameComponentDestroyer;
    class Render;
}

using std::weak_ptr;
using std::unique_ptr;
//TODO: draw is bad bleat.
namespace BEbraEngine {

    export class Line {
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
        ~Line()
        {

        }


        Vector3 from;
        Vector3 to;
        Vector3 color;

        void create(Render& render);

        void update()
        {
            _data = { from, to, color };

        }

        std::shared_ptr<RenderBufferView> data;
        std::shared_ptr<RenderBuffer> vertices;
        std::shared_ptr<Transform> transform;
    };


    export class Light : public GameComponent {
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

        //void destroy(VisitorGameComponentDestroyer& destroyer) {}//override;

        //void destroy(ÑVisitorGameComponentDestroyer auto& destroyer) {
        //    destroyer.destroyPointLightComponent(*this);
        //}


        std::shared_ptr<RenderBufferView> data;

        Transform* transform;


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


    export class DirectionLight : public GameComponent {
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
        std::shared_ptr<RenderBufferView> data;

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
            data->setData(&data1, sizeof(ShaderData), 0);
        }
        Vector3& getDirection() {
            return _direction;
        }
        Vector3& getColor() {
            return color;
        }

        DirectionLight() { name_ = "DirectionLight"; }
        virtual ~DirectionLight() {}


        //virtual void destroy(VisitorGameComponentDestroyer& destroyer) {}//override;

        //void destroy(ÑVisitorGameComponentDestroyer auto& destroyer) {
        //    destroyer.destroyDirectionLightComponent(*this);
        //}


    private:
        Vector3 color;
        Vector3 _direction;


    };

    export struct MaterialCreateInfo {
        boost::filesystem::path color;
        boost::filesystem::path specular;
        boost::filesystem::path normal;
    };

    export class Material : public GameComponent {
        //DEBUG_DESTROY_CHECK_DECL()
    public:
        friend class GameComponentDestroyer;

    public:
        Material(std::shared_ptr<Texture> color)
        {
            this->color = color;
        }

        Material(Texture* color, Texture* specular, Texture* normal)
        {
            this->color = std::shared_ptr<Texture>(color);
            this->specular = std::shared_ptr<Texture>(specular);
            this->normal = std::shared_ptr<Texture>(normal);
        }

        //void Material::destroy(VisitorGameComponentDestroyer& destroyer)
        //{
        //    destroyer.destroyMaterialComponent(*this);
        //}

        ~Material()
        {
            //DEBUG_DESTROY_CHECK("Material has not destroyed", this, "", Debug::ObjectType::Empty, Debug::MessageType::Info);
        }

        Texture& getColor() { return *color; }
        Texture& getSpecular() { return *specular; }
        Texture& getNormal() { return *normal; }

        std::shared_ptr<Texture> color;
        std::shared_ptr<Texture> specular;
        std::shared_ptr<Texture> normal;

    };

    export struct RenderObjectCreateInfo {
        const Light::CreateInfo* pointLightInfo;
        const DirectionLight::CreateInfo* directionLightInfo;
    };

    //TODO: èçáàâëÿòüñÿ îò ýòîãî êëàññà íàäî.
    export class RenderObject : public GameComponent {
        //DEBUG_DESTROY_CHECK_DECL()
    public:
        struct ShaderData {
            Matrix4 model;
            alignas(16) Vector3 color;
            int hasMaps{ false };
        };

    public:


        //void destroy(VisitorGameComponentDestroyer& destroyer) {}//override;

        //void destroy(ÑVisitorGameComponentDestroyer auto& destroyer) {
        //    destroyer.destroyRenderComponent(*this);
        //}


        Material* material;

        std::shared_ptr<Model> model;

        std::shared_ptr<RenderBufferView> matrix;

        Transform* transform;

        void update();

        virtual ~RenderObject()
        {
            //DEBUG_DESTROY_CHECK("RenderObject has not destroyed", this, "", Debug::ObjectType::RenderObject, Debug::MessageType::Info);
        }

        RenderObject()
        {
        }

        void setColor(const Vector3& color) {

            _color = color;
        }
        Vector3& getColor() {
            return _color;
        }
        bool hasMaps;
    private:
        Vector3 _color;

    };
}
