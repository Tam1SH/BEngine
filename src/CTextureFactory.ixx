#include "platform.hpp"
#include <boost/filesystem.hpp>

#include <optional>
#include <memory>

export module CTextureFactory;


using std::optional;
using std::function;

export namespace BEbraEngine {
    class Texture;
    class Material;
    class MaterialCreateInfo;
}

namespace BEbraEngine {
    
    export template<typename T>
        concept CTextureFactory = requires(

            /*optional<Material*> createMaterialAsync*/ const MaterialCreateInfo& info, function<void(Material*)> onComplete_,

            /*Texture* createAsync*/ const boost::filesystem::path& path, function<void(Texture*)> onComplete,

            /*Texture* create*/ const boost::filesystem::path& _path, bool generateMip,

            /*void destroyTexture*/ Texture& texture,

            /*void destroyTextureAsync*/ std::shared_ptr<Texture> shared_ptr_texture,

            //this 
            T& self
            )
    {
        { self.createAsync(path, onComplete) } -> std::same_as<Texture*>;

        { self.create(_path, generateMip) } -> std::same_as<Texture*>;

        { self.createEmpty() } -> std::same_as<Texture*>;

        //{ self.setDestroyer(destroyer) } -> std::same_as<void>;

        { self.createMaterialAsync(info, onComplete_) } -> std::same_as<optional<Material*>>;

        { self.destroyTexture(texture) } -> std::same_as<void>;

        { self.destroyTextureAsync(shared_ptr_texture) } -> std::same_as<void>;

    };
            
}


