#include "platform.hpp"
#include <boost/filesystem.hpp>

#include <optional>
#include <memory>

export module CTextureFactory;
//import RenderObjects;
using BE_STD::optional;
using BE_STD::function;


namespace BEbraEngine {
    /*
    export template<typename T>
        concept CTextureFactory = requires(
            // this 
            T & self,
            // parameters of interface 
            const boost::filesystem::path & path,
            function<void(Texture*)> onComplete,
            bool generateMip,
            IVisitorGameComponentDestroyer & destroyer,
            const Material::CreateInfo& info,
            Texture & texture,
            std::shared_ptr<Texture> shared_ptr_texture
            )
    {
        { self.createAsync(path, onComplete) } -> std::same_as<Texture*>;

        { self.create(path, generateMip) } -> std::same_as<Texture*>;

        { self.createEmpty() } -> std::same_as<Texture*>;

        { self.setDestroyer(destroyer) } -> std::same_as<void>;

        { self.createMaterialAsync(info, onComplete) } -> std::same_as<optional<Material*>>;

        { self.destroyTexture(texture) } -> std::same_as<Texture*>;

        { self.destroyTextureAsync(shared_ptr_texture) } -> std::same_as<void>;

    };
            */
}


