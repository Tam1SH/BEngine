#include <boost/filesystem.hpp>


export module VulkanTextureFactory;
import ITextureFactory;
import RenderObjects;
import AbstractRender;
import Debug;
import Texture;
import <optional>;
import <functional>;
import <memory>;
using std::shared_ptr;
using std::function;
using std::optional;

namespace BEbraEngine {
    class VulkanRender;
}

namespace BEbraEngine {
    export class VulkanTextureFactory : public ITextureFactory {
    public:

        optional<Material*> createMaterialAsync(const MaterialCreateInfo& info, function<void(Material*)> onComplete); //override;

        Texture* createAsync(const boost::filesystem::path& path, function<void(Texture*)> onComplete); //override;

        Texture* create(const boost::filesystem::path& path, bool generateMip); //override;

        Texture* createEmpty(); //override;

        void saveImage(const char* fileName, int width, int height, int channel_num, const void* rows, int quality);
        
        void saveImage(const char* fileName, int width, int height, int channel_num, BEbraEngine::BitMap& bitMap, int quality);

        void setDestroyer(IVisitorGameComponentDestroyer& destroyer); //override;

        void destroyTexture(Texture& texture); //override;

        void destroyTextureAsync(shared_ptr<Texture> texture); //override;

        VulkanTextureFactory(AbstractRender* render);

    private:
        VulkanRender* render;
        IVisitorGameComponentDestroyer* destroyer;

    };
}