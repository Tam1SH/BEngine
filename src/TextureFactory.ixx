#include "platform.hpp"
#include <boost/filesystem.hpp>

export module TextureFactory;
import <optional>;
import <memory>;
import Texture;
import RenderObjects;
import VisitorGameComponentDestroyer;
using std::optional;
using std::function;

namespace BEbraEngine {

    export class TextureFactory {
    public:
        virtual Texture* createAsync(const boost::filesystem::path& path, function<void(Texture*)> onComplete) = 0;

        virtual Texture* create(const boost::filesystem::path& path, bool generateMip) = 0;

        virtual Texture* createEmpty() = 0;

        virtual void setDestroyer(VisitorGameComponentDestroyer& destroyer) = 0;

        virtual optional<Material*> createMaterialAsync(const MaterialCreateInfo& info, function<void(Material*)> onComplete) = 0;

        virtual void destroyTexture(Texture& texture) = 0;

        virtual void destroyTextureAsync(std::shared_ptr<Texture> texture) = 0;

        virtual ~TextureFactory() {}

    };
}