
#include "stdafx.h"

#include "VulkanTextureFactory.hpp"
#include "stb_image.h"
#include "VulkanRender.hpp"
#include "Debug.hpp"

namespace BEbraEngine {
    Texture* VulkanTextureFactory::createAsync(const std::filesystem::path& path, std::function<void(Texture*)> onComplete)
    {
        Texture* image = new Texture();
        VkDeviceMemory textureImageMemory{};
        VkImage textureImage{};
        int texWidth{}, texHeight{}, texChannels{};
        stbi_set_flip_vertically_on_load(true);

        auto str = ((path.parent_path().string() / path.stem()).string() + "_low");
        auto str1 = path.extension().string();

        std::string path_low = str + str1;
        stbi_uc* pixels = stbi_load(path_low.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        VkDeviceSize imageSize = texWidth * texHeight * 4;
        render->createVkImage(pixels, texWidth, texHeight, textureImage, textureImageMemory, imageSize);
        stbi_image_free(pixels);
        auto imageView = render->createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
        VkSampler sampler;
        render->createTextureSampler(sampler);

        tbb::task_arena g;
        g.enqueue([=] {
            auto str = ((path.parent_path().string() / path.stem()).string());
            auto str1 = path.extension().string();

            std::string path = str + str1;
            Texture* image = create(path);
            onComplete(image);
            });

        image->self = textureImage;
        image->imageView = imageView;
        image->sampler = sampler;
        image->memory = textureImageMemory;
        image->width = texWidth;
        image->height = texHeight;
        image->path = "nothing";
        //delete[] pixels;
        return image;
    }
    Texture* VulkanTextureFactory::createEmpty()
    {
        Texture* image = new Texture();
        VkDeviceMemory textureImageMemory{};
        VkImage textureImage{};
        int texWidth = 1, texHeight = 1, texChannels;
        stbi_set_flip_vertically_on_load(true);

        stbi_uc* pixels = new unsigned char[1];
        VkDeviceSize imageSize = texWidth * texHeight * 4;
        //stbi_image_free(pixels);



        render->createVkImage(pixels, texWidth, texHeight, textureImage, textureImageMemory, imageSize);


        auto imageView = render->createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
        VkSampler sampler;
        render->createTextureSampler(sampler);


        image->self = textureImage;
        image->imageView = imageView;
        image->sampler = sampler;
        image->memory = textureImageMemory;
        image->width = texWidth;
        image->height = texHeight;
        image->path = "nothing";
        delete[] pixels;
        return image;
    }
    Texture* VulkanTextureFactory::create(const std::string& path)
    {
        Texture* image = new Texture();
        VkDeviceMemory textureImageMemory{};
        VkImage textureImage{};
        int texWidth, texHeight, texChannels;
        stbi_set_flip_vertically_on_load(true);

        stbi_uc* pixels = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        VkDeviceSize imageSize = texWidth * texHeight * 4;


        render->createVkImage(pixels, texWidth, texHeight, textureImage, textureImageMemory, imageSize);
        auto imageView = render->createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
        VkSampler sampler;
        render->createTextureSampler(sampler);


        image->self = textureImage;
        image->imageView = imageView;
        image->sampler = sampler;
        image->memory = textureImageMemory;
        image->width = texWidth;
        image->height = texHeight;
        image->path = "nothing";
        return image;
    }
    VulkanTextureFactory::VulkanTextureFactory(AbstractRender* render) : render(dynamic_cast<VulkanRender*>(render))
    {
    }
}
