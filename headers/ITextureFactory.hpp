
#include "stdafx.h"
#include "platform.hpp"
#include "RenderObject.hpp"
using BE_STD::optional;
using BE_STD::function;

namespace BEbraEngine {
    class Texture;
    class Material;
    class IVisitorGameComponentDestroyer;
}
namespace BEbraEngine {

    class ITextureFactory {
    public:
        virtual Texture* createAsync(const boost::filesystem::path& path, function<void(Texture*)> onComplete) = 0;

        virtual Texture* create(const boost::filesystem::path& path, bool generateMip) = 0;

        virtual Texture* createEmpty() = 0;

        virtual void setDestroyer(IVisitorGameComponentDestroyer& destroyer) = 0;

        virtual optional<Material*> createMaterialAsync(const Material::CreateInfo& info, function<void(Material*)> onComplete) = 0;

        virtual void destroyTexture(Texture& texture) = 0;

        virtual ~ITextureFactory() {}

    };
}