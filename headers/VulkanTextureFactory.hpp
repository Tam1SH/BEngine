#pragma once

#include "stdafx.h"
#include "Texture.hpp"
#include "ITextureFactory.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

namespace BEbraEngine {
    class AbstractRender;
    class VulkanRender;
}

namespace BEbraEngine {
    class VulkanTextureFactory final : public ITextureFactory {
    public:

        optional<Material*> createMaterialAsync(const Material::CreateInfo& info, function<void(Material*)> onComplete) override;

        Texture* createAsync(const boost::filesystem::path& path, function<void(Texture*)> onComplete) override;

        Texture* create(const boost::filesystem::path& path, bool generateMip) override;

        Texture* createEmpty() override;

        void setDestroyer(IVisitorGameComponentDestroyer& destroyer) override;

        void jopa(char const* filename, int x, int y, int comp, const void* data, int quality);

        void destroyTexture(Texture& texture) override;

        VulkanTextureFactory(AbstractRender* render);

    private:
        VulkanRender* render;
        IVisitorGameComponentDestroyer* destroyer;

    };
}