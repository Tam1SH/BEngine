
#pragma once
#include "stdafx.h"
#include "AbstractComponent.hpp"
//TODO: Ну, понятно.
namespace BEbraEngine {
    
    class Texture : public GameObjectComponent {
    public:
        std::string path;
        bool _isLoad;
        unsigned char* picture;
        int width;
        int height;
        int Channels;

        VkBuffer buf;
        VkImage self;
        VkImageView imageView;
        VkSampler sampler;
        VkDeviceMemory memory;
        Texture(VkImage& self, VkImageView& imageView, VkSampler& sampler, VkDeviceMemory& textureImageMemory) : self(self), imageView(imageView), sampler(sampler), memory(textureImageMemory) {}
        Texture() {}
        bool IsLoad() {
            return _isLoad;
        }
        void SetLoad(bool b) {
            _isLoad = b;
        }
        VkImageView GetView() {
            return imageView;
        }
        VkSampler GetSampler() {
            return sampler;
        }
        VkDeviceMemory GetMemory() {
            return memory;
        }
        VkImage GetImage() {
            return self;
        }

        ~Texture();

    };
    class VulkanTexture : public Texture {
    public:
        bool isLoad;
        int width;
        int height;

        VkImage image;
        VkImageView imageView;
        VkSampler sampler;
        VkDeviceMemory memory;
    };
}