module;
#include "stdafx.h"
export module Light;
import GameComponent;
import Vector3;
import RenderBufferView;
import Transform;


namespace BEbraEngine {

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
        template<typename Destroyer>
        void destroy(Destroyer& destroyer) {
            destroyer.destroyLight(*this);
        }

        RenderBufferView* data;

        Transform* transform;


        void setColor(const Vector3& color) {

            this->color = color;
        }

        Vector3& getColor() {
            return color;
        }

        void update()
        {
            ShaderData _data;
            _data.position = transform->getPosition();
            _data.color = color;
            _data.diffuse = color;
            _data.specular = color;
            _data.constant = 1.f;
            _data.linear = 0.022f;
            _data.quadratic = 0.0019f;
            data->setData(&_data, sizeof(ShaderData), 0);

        }


        Light() { name_ = "Light"; }
        virtual ~Light() {}
    private:
        Vector3 color;

    };



}