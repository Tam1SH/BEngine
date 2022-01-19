
#pragma once
#include "stdafx.h"
#include "GameComponent.hpp"
#include "Debug.hpp"
//TODO: Ну, понятно.
namespace BEbraEngine {
    
    class Texture : public GameComponent { DEBUG_DESTROY_CHECK_DECL()
    public:
        Texture();
        ~Texture();
        uint32_t width() { return width_; }
        uint32_t height() { return height_; }

        void destroy(IVisitorGameComponentDestroyer& destroyer) override;

    protected:
        uint32_t width_{};
        uint32_t height_{};



        

    };

    class VulkanTexture : public Texture {
    public:
        void setWidth(uint32_t value) { width_ = value; }
        void setHeight(uint32_t value) { height_ = value; }
        VulkanTexture& operator=(VulkanTexture&& other) noexcept {
            if (this == &other) return *this;
            image = other.image;
            memory = other.memory;
            imageView = other.imageView;
            sampler = other.sampler;
            other.image = 0;
            other.memory = 0;
            other.imageView = 0;
            other.sampler = 0;

            return *this;
        }
        VulkanTexture() {}
        VulkanTexture(VulkanTexture&& other) noexcept {
            if (this == &other) return;
            image = other.image;
            memory = other.memory;
            imageView = other.imageView;
            sampler = other.sampler;
            other.image = 0;
            other.memory = 0;
            other.imageView = 0;
            other.sampler = 0;
        }
        uint32_t mipLevels;
        VkImage image;
        VkImageView imageView;
        VkSampler sampler;
        VkDeviceMemory memory;
    };
}