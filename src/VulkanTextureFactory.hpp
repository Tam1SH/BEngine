
#pragma once
#include "stdafx.h"
#include "VulkanRender.hpp"
#include <stb-master/stb_image.h>
#include "Image.hpp"
//#include <tbb.h>

//TODO: Сделать независимым от апи.
namespace BEbraEngine {
    class ITextureFactory {
        virtual Texture* createAsync(const std::string& path) = 0;
        virtual Texture* create(const std::string& path) = 0;
    };
    class VulkanTextureFactory : public ITextureFactory {
    public:
        Texture* createAsync(const std::string& path) override { return 0; }
        Texture* create(const std::string& path) override { return 0; }

        stbi_uc* loadImage(const std::string& path, int* texWidth, int* texHeight, int* texChannels) {
            auto pic = stbi_load(path.c_str(), texWidth, texHeight, texChannels, STBI_rgb_alpha);

        }
        Texture loadImageAsync(const std::string& path) {
            Texture picture;

        }
        Texture loadImage1(const std::string& path) {
            Texture pic;
            pic.picture = stbi_load(path.c_str(), &pic.Width, &pic.Height, &pic.Channels, STBI_rgb_alpha);
            return pic;
        }
        Texture* CreateAsync(const std::string& path) {
            /*
            Texture* image = new Texture();
            image = createEmptyTexture();
            image->SetLoad(false);
            image->path = path;
            tbb::task_arena task;

            images.push_back(image);
            task.enqueue([image, path, this] {
                image->picture = stbi_load(path.c_str(), &image->Width, &image->Height, &image->Channels, STBI_rgb_alpha);
                startUpdateImage(*image, image->picture, image->Width, image->Height, image->Channels);
                endUpdateImage(*image);
                image->SetLoad(true);
                });

            return image;
            */
        }
        Texture* CreateAsync1(const std::string& path, VkCommandBuffer& buffer) {
            Texture* image = new Texture();

            image->SetLoad(false);
            image->path = path;
            //tbb::task_arena task;
            stbi_set_flip_vertically_on_load(true);
            //images.push_back(image);
            image->picture = stbi_load(path.c_str(), &image->Width, &image->Height, &image->Channels, STBI_rgb_alpha);
            auto _render = static_cast<VulkanRender*>(render);
            _render->createVkImage2(image->picture, image->Width, image->Height, image->self, image->memory, buffer);
            auto imageView = _render->createImageView(image->self, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
            VkSampler sampler;
            _render->createTextureSampler(sampler);
            image->SetLoad(true);
            image->imageView = imageView;
            image->sampler = sampler;

            return image;

        }
        Texture* createEmptyTexture()
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
        Texture* createTexture(const std::string& path)
        {
            Texture* image = new Texture();
            VkDeviceMemory textureImageMemory = 0;
            VkImage textureImage;
            int texWidth, texHeight, texChannels;
            stbi_set_flip_vertically_on_load(true);

            stbi_uc* pixels = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
            VkDeviceSize imageSize = texWidth * texHeight * 4;

            VkBuffer stagingBuffer;
            VkDeviceMemory stagingBufferMemory;
            auto _render = static_cast<VulkanRender*>(render);
            _render->_createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

            void* data;

            vkMapMemory(_render->GetDevice(), stagingBufferMemory, 0, imageSize, 0, &data);
            memcpy(data, pixels, static_cast<size_t>(imageSize));
            vkUnmapMemory(_render->GetDevice(), stagingBufferMemory);

            stbi_image_free(pixels);

            _render->createVkImage(pixels, texWidth, texHeight, textureImage, textureImageMemory, imageSize, stagingBuffer);
            auto imageView = _render->createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
            VkSampler sampler;
            _render->createTextureSampler(sampler);

            vkDestroyBuffer(VulkanRender::device, stagingBuffer, 0);
            vkFreeMemory(VulkanRender::device, stagingBufferMemory, 0);


            image->self = textureImage;
            image->imageView = imageView;
            image->sampler = sampler;
            image->memory = textureImageMemory;
            image->picture = pixels;
            image->Width = texWidth;
            image->Height = texHeight;
            image->path = path;
            return image;
        }
        Texture* createEmptyTexture2(VkCommandBuffer& buffer)
        {
            Texture* image = new Texture();
            VkDeviceMemory textureImageMemory;
            VkImage textureImage;
            int texWidth, texHeight, texChannels;
            stbi_set_flip_vertically_on_load(true);
            texWidth = 1;
            texHeight = 1;
            stbi_uc* pixels = new unsigned char[3];//stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
            pixels[0] = rand() % 256;
            pixels[1] = rand() % 256;
            pixels[2] = rand() % 256;
            auto _render = static_cast<VulkanRender*>(render);
            _render->createVkImage2(pixels, texWidth, texHeight, textureImage, textureImageMemory, buffer);
            auto imageView = _render->createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
            VkSampler sampler;
            _render->createTextureSampler(sampler);
            //stbi_image_free(pixels);
            *image = Texture(textureImage, imageView, sampler, textureImageMemory);
            image->Width = texWidth;
            image->Height = texHeight;
            return image;
        }
        void UpdateImage(Texture& img, stbi_uc* picture, int texWidth, int texHeight, int texChannels) {
            Texture imgcopy;
            VkDeviceMemory textureImageMemory;
            VkImage textureImage;
            auto _render = static_cast<VulkanRender*>(render);
            //render->createVkImage(picture, texWidth, texHeight, textureImage, textureImageMemory);
            auto imageView = _render->createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
            VkSampler sampler;
            _render->createTextureSampler(sampler);
            img = Texture(textureImage, imageView, sampler, textureImageMemory);
            //stbi_image_free(picture);

        }
        void startUpdateImage(Texture& img, stbi_uc* picture, int texWidth, int texHeight, int texChannels) {
            VkDeviceSize imageSize = texWidth * texHeight * 4;
            auto _render = static_cast<VulkanRender*>(render);
            _render->_createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, img.buf, img.memory);

            void* data;
            vkMapMemory(_render->GetDevice(), img.memory, 0, imageSize, 0, &data);
            memcpy(data, picture, static_cast<size_t>(imageSize));
            vkUnmapMemory(_render->GetDevice(), img.memory);
            _render->createImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, img.self, img.memory);
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
            if (vkBeginCommandBuffer(_render->_copyBuffer, &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }
            _render->transitionImageLayout(img.self, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, _render->_copyBuffer);
            _render->copyBufferToImage(img.buf, img.self, static_cast<uint32_t>(img.Width), static_cast<uint32_t>(img.Height), _render->_copyBuffer);
            _render->transitionImageLayout(img.self, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, _render->_copyBuffer);

            vkEndCommandBuffer(_render->_copyBuffer);
            //stbi_image_free(picture);
            //
        }
        void endUpdateImage(Texture& img) {
            auto _render = static_cast<VulkanRender*>(render);
            _render->createVkImage1();
            auto imageView = _render->createImageView(img.self, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
            VkSampler sampler;
            _render->createTextureSampler(sampler);
            img.sampler = sampler;
            img.imageView = imageView;
            //stbi_image_free(picture);

        }
        void CheakReadyPicture() {
            int xyu = 0;
            for (auto image : images) {
                if (image->IsLoad()) {
                    startUpdateImage(*image, image->picture, image->Width, image->Height, image->Channels);
                    endUpdateImage(*image);
                    images.erase(images.begin() + xyu);
                    return;
                    //free(image->picture);
                }
                xyu++;
            }
        }

        VulkanTextureFactory(AbstractRender* render) : render(render) {}
        private:
            AbstractRender* render;
            std::vector<Texture*> images;
    };
}