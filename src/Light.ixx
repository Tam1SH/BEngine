module;
export module Light;
import GameComponent;
import Vector3;
import Transform;
import RenderBufferView;
import <memory>;

namespace BEbraEngine {

    export struct Light : GameComponent {

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