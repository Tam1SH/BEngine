#pragma once
#include "stdafx.h"
#include "Image.hpp"
#include "ITextureFactory.hpp"

namespace BEbraEngine {
    class AbstractRender;
}
namespace BEbraEngine {
    class VulkanTextureFactory : public ITextureFactory {
    public:
        Texture* createAsync(const std::string& path) override { return 0; }
       // Texture* create(const std::string& path) override { return 0; }

        Texture* createEmpty() override;

        Texture* create(const std::string& path) override;


        VulkanTextureFactory(AbstractRender* render) : render(render) {}

        private:
            AbstractRender* render;
    };
}