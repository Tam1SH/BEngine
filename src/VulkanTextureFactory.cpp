
#include "stdafx.h"

#include "VulkanTextureFactory.hpp"
#include <stb-master/stb_image.h>

#include "VulkanRender.hpp"
#include "Debug.hpp"

namespace BEbraEngine {

    Texture* VulkanTextureFactory::createAsync(const boost::filesystem::path& path, std::function<void(Texture*)> onComplete)
    {

        auto str = ((path.parent_path().string() / path.stem()).string() + "_low");
        auto str1 = path.extension().string();
        auto path_low = str + str1;
        auto image = create(path_low, false);

        tbb::task_arena g;
        g.enqueue([=] {
            auto str = ((path.parent_path().string() / path.stem()).string());
            auto str1 = path.extension().string();

            std::string path = str + str1;
            Texture* image = create(path, true);
            onComplete(image);
        });

        return image;
    }
    Texture* VulkanTextureFactory::create(const boost::filesystem::path& path, bool generateMip)
    {
        VulkanTexture* image = new VulkanTexture();
        int texWidth, texHeight, texChannels;
        stbi_set_flip_vertically_on_load(true);

        stbi_uc* pixels = stbi_load(path.string().c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        image->setHeight(texHeight);
        image->setWidth(texWidth);
        VkDeviceSize imageSize = texWidth * texHeight * 4;

        if (!pixels)
        {
            if(!path.string().empty())
                DEBUG_LOG2("failed to upload texture. uncorrect path or file don't exist. | path: " + path.string(),
                    image, "", Debug::ObjectType::Empty, Debug::MessageType::Error);
            pixels = new unsigned char[4]{ 255,255,255 };
            texWidth = 1, texHeight = 1;
            imageSize = 4;
            image->setHeight(texHeight);
            image->setWidth(texWidth);
        }
        if (generateMip)
            image->mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;
        else
            image->mipLevels = 1;

        render->createVkImage(pixels, image, imageSize);
        image->imageView = render->createImageView(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
        stbi_image_free(pixels);
        
        render->createTextureSampler(image);

        return image;
    }
    Texture* VulkanTextureFactory::createEmpty()
    {
        return create("", false);
    }
    VulkanTextureFactory::VulkanTextureFactory(AbstractRender* render) : render(dynamic_cast<VulkanRender*>(render))
    { 
        if (!render) throw std::runtime_error("render isn't VulkanRender"); 
    }
    void VulkanTextureFactory::destroyTexture(Texture* texture)
    {
        auto vTexture = static_cast<VulkanTexture*>(texture);
        render->destroyTexture(vTexture);

#ifdef _DEBUG
        texture->isDestroyed = true;
#endif 


    }
}
