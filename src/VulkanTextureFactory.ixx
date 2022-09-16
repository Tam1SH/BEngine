#include <boost/filesystem.hpp>
export module VulkanTextureFactory;
import VulkanRender;
import Material;
import Debug;
import Render;
import Texture;

import <optional>;
import <functional>;
import <memory>;

using std::shared_ptr;
using std::function;
using std::optional;

namespace BEbraEngine {
    export class VulkanTextureFactory {
    public:

        optional<Material*> createMaterialAsync(const MaterialCreateInfo& info, function<void(Material*)> onComplete);

        Texture* createAsync(const boost::filesystem::path& path, function<void(Texture*)> onComplete);

        Texture* create(const boost::filesystem::path& path, bool generateMip);

        Texture* createEmpty();

        void saveImage(const char* fileName, int width, int height, int channel_num, const void* rows, int quality);
        
        void saveImage(const char* fileName, int width, int height, int channel_num, BEbraEngine::BitMap& bitMap, int quality);

       // void setDestroyer(VisitorGameComponentDestroyer& destroyer); //override;

        void destroyTexture(Texture& texture);

        void destroyTextureAsync(shared_ptr<Texture> texture);

        VulkanTextureFactory(VulkanRender& render);

    private:
        VulkanRender& render;
        //VisitorGameComponentDestroyer* destroyer;

    };
}

module :private;
import CTextureFactory;

namespace BEbraEngine {
    static_assert(CTextureFactory<VulkanTextureFactory>);
}