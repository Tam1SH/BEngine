module;
#include <memory>
export module DirectionLight;
import GameComponent;
import Vector3;

namespace BEbraEngine {
    export struct RenderBufferView;
}

namespace BEbraEngine {


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

        template<typename Destroyer>
        void destroy(Destroyer& destroyer) {
            destroyer.destroyLight(*this);
        }

        std::shared_ptr<RenderBufferView> data;

        void setColor(const Vector3& color) {

            this->color = color;
        }
        void setDirection(const Vector3& direction) {
            _direction = direction;
        }
        void update();

        Vector3& getDirection() {
            return _direction;
        }
        Vector3& getColor() {
            return color;
        }

        DirectionLight() { name_ = "DirectionLight"; }
        virtual ~DirectionLight() {}





    private:
        Vector3 color;
        Vector3 _direction;
    
    };

}