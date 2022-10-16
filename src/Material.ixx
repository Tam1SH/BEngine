module;
#include <boost/filesystem.hpp>
export module Material;
import GameComponent;
import Texture;
import OnlyMovable;
import GameComponentDestroyerDecl;
import <memory>;


namespace BEbraEngine {

    export struct MaterialCreateInfo {
        boost::filesystem::path color;
        boost::filesystem::path specular;
        boost::filesystem::path normal;
    };

    export class Material : public GameComponent {
    public:


        void destroy(GameComponentDestroyer& destroyer) override;

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