#pragma once

#include "stdafx.h"
#include "Texture.hpp"
#include "ITextureFactory.hpp"
#define STB_IMAGE_IMPLEMENTATION

namespace BEbraEngine {
    class AbstractRender;
    class VulkanRender;
}

namespace BEbraEngine {
    class VulkanTextureFactory final : public ITextureFactory {
    public:
        Texture* createAsync(const boost::filesystem::path& path, std::function<void(Texture*)> onComplete) override;

        Texture* create(const boost::filesystem::path& path, bool generateMip) override;

        Texture* createEmpty() override;

        void destroyTexture(Texture* texture) override;

        VulkanTextureFactory(AbstractRender* render);

        private:
            VulkanRender* render;

    };
}