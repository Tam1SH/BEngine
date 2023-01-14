export module TextureFactory;
import Task;
import Material;
import Texture;
import stdDeclaration;
import TextureData;
namespace BEbraEngine {

    export struct TextureFactory {
        virtual Task<optional<Material*>> createMaterialAsync(const MaterialCreateInfo& info) = 0;

        virtual Task<optional<Texture*>> createAsync(const CreateTextureInfo& info) = 0;

        virtual optional<Texture*> createEmpty() = 0;
        
        virtual void destroyTextureAsync(shared_ptr<Texture> texture) = 0;

    };


}
