module;

export module RenderObject;
import GameComponent;
import Matrix4;
import Vector3;
import Material;
import RenderBuffer;
import RenderBufferView;
import Transform;
import <memory>;

namespace BEbraEngine {
    export struct Model;
}
namespace BEbraEngine {

    export struct RenderObjectCreateInfo {

        struct LightCreateInfo {
            const Vector3 lightColor{ 1 };
            float constant{};
            float linear{};
            float quadratic{};
        };

        struct DirectionLightCreateInfo {
            const Vector3 lightColor{ 1 };
        };

        const LightCreateInfo* lightCreateInfo;
        const DirectionLightCreateInfo* directionLightInfo;
    };

    export struct RenderObject : GameComponent {

        struct ShaderData {
            Matrix4 model;
            alignas(16) Vector3 color;
            int hasMaps{ false };
        };

        template<typename Destroyer>
        void destroy(Destroyer& destroyer) {
            destroyer.destroyRenderObject(*this);
        }

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
