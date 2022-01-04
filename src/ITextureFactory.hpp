
#include "stdafx.h"

namespace BEbraEngine {
    class Texture;
}
namespace BEbraEngine {

    class ITextureFactory {
    public:
        virtual Texture* createAsync(const boost::filesystem::path& path, std::function<void(Texture*)> onComplete) = 0;

        virtual Texture* create(const boost::filesystem::path& path, bool generateMip) = 0;

        virtual Texture* createEmpty() = 0;

        virtual void destroyTexture(Texture* texture) = 0;

        virtual ~ITextureFactory() {}

    };
}