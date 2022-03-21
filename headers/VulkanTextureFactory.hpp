#pragma once

#include "stdafx.h"
#include "Texture.hpp"
#include "ITextureFactory.hpp"
#include "AbstractRender.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

namespace BEbraEngine {
    class VulkanRender;
}

namespace BEbraEngine {
    class VulkanTextureFactory final : public ITextureFactory {
    public:

        optional<Material*> createMaterialAsync(const Material::CreateInfo& info, function<void(Material*)> onComplete) override;

        Texture* createAsync(const boost::filesystem::path& path, function<void(Texture*)> onComplete) override;

        Texture* create(const boost::filesystem::path& path, bool generateMip) override;

        Texture* createEmpty() override;
        
        void saveImage(const char* fileName, int width, int height, int channel_num, const BitMap& pixels, int quality);

        void setDestroyer(IVisitorGameComponentDestroyer& destroyer) override;

        void destroyTexture(Texture& texture) override;

        void destroyTextureAsync(shared_ptr<Texture> texture) override;

        VulkanTextureFactory(AbstractRender* render);

    private:
        VulkanRender* render;
        IVisitorGameComponentDestroyer* destroyer;

    };
}