module;
#include <memory>
#include <string>
export module Material;
import GameComponent;
import Texture;
import Concepts;

namespace BEbraEngine {

    export struct MaterialCreateInfo {
        std::string color;
        std::string specular;
        std::string normal;
    };

    export struct Material : GameComponent {

        template<typename Destroyer>
        void destroy(Destroyer& destroyer) {
            //destroyer.destroyLight(*this);
        }

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

    //static_assert()
}