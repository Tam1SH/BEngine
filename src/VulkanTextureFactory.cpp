#include "stdafx.h"
#include "VulkanTextureFactory.hpp"

#include "VulkanRender.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace BEbraEngine {

    Texture* VulkanTextureFactory::createEmpty()
    {
        Texture* image = new Texture();
        VkDeviceMemory textureImageMemory = 0;
        VkImage textureImage;
        int texWidth = 1, texHeight = 1, texChannels;
        stbi_set_flip_vertically_on_load(true);

        stbi_uc* pixels = new unsigned char[1];
        VkDeviceSize imageSize = texWidth * texHeight * 4;
        //stbi_image_free(pixels);
        auto _render = static_cast<VulkanRender*>(render);




        _render->createVkImage(pixels, texWidth, texHeight, textureImage, textureImageMemory, imageSize);
        auto imageView = _render->createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
        VkSampler sampler;
        _render->createTextureSampler(sampler);


        image->self = textureImage;
        image->imageView = imageView;
        image->sampler = sampler;
        image->memory = textureImageMemory;
        image->picture = pixels;
        image->Width = texWidth;
        image->Height = texHeight;
        image->path = "nothing";
        return image;
    }
    Texture* VulkanTextureFactory::create(const std::string& path)
    {
        Texture* image = new Texture();
        VkDeviceMemory textureImageMemory = 0;
        VkImage textureImage;
        int texWidth, texHeight, texChannels;
        //stbi_set_flip_vertically_on_load(true);

        stbi_uc* pixels = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        VkDeviceSize imageSize = texWidth * texHeight * 4;

        auto _render = static_cast<VulkanRender*>(render);

        _render->createVkImage(pixels, texWidth, texHeight, textureImage, textureImageMemory, imageSize);
        auto imageView = _render->createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
        VkSampler sampler;
        _render->createTextureSampler(sampler);

        // vkDestroyBuffer(VulkanRender::device, stagingBuffer, 0);
       //  vkFreeMemory(VulkanRender::device, stagingBufferMemory, 0);


        image->self = textureImage;
        image->imageView = imageView;
        image->sampler = sampler;
        image->memory = textureImageMemory;
        image->picture = pixels;
        image->Width = texWidth;
        image->Height = texHeight;
        image->path = "nothing";
        return image;
    }
}
