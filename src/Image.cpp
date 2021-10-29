#include "stdafx.h"
#include "Image.hpp"
#include "BaseVulkanRender.hpp"
namespace BEbraEngine {
    Texture::~Texture()
    {
        vkFreeMemory(BaseVulkanRender::device, memory, 0);
        vkDestroyImage(BaseVulkanRender::device, self, 0);
        vkDestroyImageView(BaseVulkanRender::device, imageView, 0);
        vkDestroySampler(BaseVulkanRender::device, sampler, 0);

    }
}