#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include "AbstractComponent.hpp"
namespace BEbraEngine {
    class Texture : public AbstractComponent {
    public:
        std::string path;
        bool _isLoad;
        unsigned char* picture;
        int Width;
        int Height;
        int Channels;

        VkBuffer buf;
        VkImage self;
        VkImageView view;
        VkSampler sampler;
        VkDeviceMemory memory;
        Texture(VkImage& self, VkImageView& view, VkSampler& sampler, VkDeviceMemory& textureImageMemory) : self(self), view(view), sampler(sampler), memory(textureImageMemory) {}
        Texture() {}
        bool IsLoad() {
            return _isLoad;
        }
        void SetLoad(bool b) {
            _isLoad = b;
        }
        VkImageView GetView() {
            return view;
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
}