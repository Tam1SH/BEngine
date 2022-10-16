export module DirectionLight;
import GameComponent;
import Vector3;
import RenderBuffer;
import GameComponentDestroyerDecl;

import <memory>;


namespace BEbraEngine {

    //Рендер-компоненты по интерфейсу выглядят отвратительно.
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

        void destroy(GameComponentDestroyer& destroyer) override;

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





    private:
        Vector3 color;
        Vector3 _direction;

    };
}