export module CTextureFactory;
import Task;
import <optional>;
import <functional>;
import <string>;
import <memory>;

using std::optional;
using std::function;

export namespace BEbraEngine {
    struct Texture;
    struct Material;
    struct MaterialCreateInfo;
}

namespace BEbraEngine {
    
    export template<typename T>
        concept CTextureFactory = requires(

            /*Task<optional<Material*>> createMaterialAsync*/ const MaterialCreateInfo& info,

            /*Task<optional<Texture*>> createAsync*/ const std::string& path,

            /*Texture* create*/ const std::string& _path, bool generateMip,

            /*void destroyTexture*/ Texture& texture,

            /*void destroyTextureAsync*/ std::shared_ptr<Texture> shared_ptr_texture,

            //this 
            T& self
            )
    {
        { self.createAsync(path) } -> std::same_as<Task<optional<Texture*>>>;

        { self.create(_path, generateMip) } -> std::same_as<Texture*>;

        { self.createEmpty() } -> std::same_as<Texture*>;

        //{ self.setDestroyer(destroyer) } -> std::same_as<void>;

        { self.createMaterialAsync(info) } -> std::same_as<Task<optional<Material*>>>;

        { self.destroyTexture(texture) } -> std::same_as<void>;

        { self.destroyTextureAsync(shared_ptr_texture) } -> std::same_as<void>;

    };
            
}


