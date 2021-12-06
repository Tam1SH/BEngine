#pragma once

#include "stdafx.h"
#include "Image.hpp"
#include "ITextureFactory.hpp"
#define STB_IMAGE_IMPLEMENTATION

namespace BEbraEngine {
    class AbstractRender;
    class VulkanRender;
}
namespace BEbraEngine {
    class VulkanTextureFactory : public ITextureFactory {
    public:
        Texture* createAsync(const std::filesystem::path& path, std::function<void(Texture*)> onComplete) override;

       // Texture* create(const std::string& path) override { return 0; }

        Texture* createEmpty() override;

        Texture* create(const std::string& path) override;


        VulkanTextureFactory(AbstractRender* render);

        private:
            VulkanRender* render;
    };
}