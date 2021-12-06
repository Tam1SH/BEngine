
#pragma once
#include "stdafx.h"
#include "AbstractComponent.hpp"
//TODO: Ну, понятно.
namespace BEbraEngine {
    
    class Texture : public GameObjectComponent {
    public:
        std::string path;
        bool _isLoad;
        int width;
        int height;
        int Channels;

        VkImage self;
        VkImageView imageView;
        VkSampler sampler;
        VkDeviceMemory memory;
        Texture(VkImage& self, VkImageView& imageView, VkSampler& sampler, VkDeviceMemory& textureImageMemory) : self(self), imageView(imageView), sampler(sampler), memory(textureImageMemory) {}
        Texture() { }

        Texture(Texture&& other) {
            width = other.width;
            height = other.height;
            self = other.self;
            imageView = other.imageView;
            sampler = other.sampler;
            memory = other.memory;
            other.width = 0;
            other.height = 0;
            other.self = 0;
            other.imageView = VK_NULL_HANDLE;
            other.sampler = VK_NULL_HANDLE;
            other.memory = VK_NULL_HANDLE;
        }
        Texture& operator=(Texture&& other) {
            width = other.width;
            height = other.height;
            self = other.self;
            imageView = other.imageView;
            sampler = other.sampler;
            memory = other.memory;
            other.width = 0;
            other.height = 0;
            other.self = 0;
            other.imageView = VK_NULL_HANDLE;
            other.sampler = VK_NULL_HANDLE;
            other.memory = VK_NULL_HANDLE;
            return *this;
        }

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