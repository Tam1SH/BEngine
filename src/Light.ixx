module;
export module Light;
import GameComponent;
import Vector3;
import Transform;
import RenderBufferView;
import PoolObject;
import <memory>;

namespace BEbraEngine {

    export struct LightCreateInfo {
        Vector3 color;
        Vector3 position;
        Vector3 lightColor{ 1 };
        float constant{};
        float linear{};
        float quadratic{};
    };

    export struct Light : GameComponent, PoolObject<Light> {

        struct ShaderData {
            alignas(16) Vector3 position;

            alignas(16) Vector3 color;
            alignas(16) Vector3 diffuse;
            alignas(16) Vector3 specular;

            alignas(4) float constant;
            alignas(4) float linear;
            alignas(4) float quadratic;
        };

        template<typename Destroyer>
        void destroy(Destroyer& destroyer) {
            destroyer.destroyLight(*this);
        }

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

}