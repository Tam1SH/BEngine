export module CTextureFactory;
import Task;
import stdDeclaration;
import TextureData;
import stdDeclaration;
import <string>;


export namespace BEbraEngine {
    struct Texture;
    struct Material;
    struct MaterialCreateInfo;
}

namespace BEbraEngine {
    
    export template<typename T>
        concept CTextureFactory = requires(

            /*Task<optional<Material*>> createMaterialAsync*/ const MaterialCreateInfo& info,

            /*Task<optional<Texture*>> createAsync*/ const CreateTextureInfo& info_,

            /*optional<Texture*> createEmpty*/

            /*void destroyTextureAsync*/ shared_ptr<Texture> texture,

            //this 
            T& self
            )
    {
        { self.createAsync(info_) } -> std::same_as<Task<optional<Texture*>>>;

        { self.createEmpty() } -> std::same_as<optional<Texture*>>;

        { self.createMaterialAsync(info) } -> std::same_as<Task<optional<Material*>>>;

        { self.destroyTextureAsync(texture) } -> std::same_as<void>;

    };
            
}


