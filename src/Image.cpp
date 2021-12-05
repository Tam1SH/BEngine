#include "stdafx.h"
#include "Image.hpp"
#include "VulkanRender.hpp"
#include "Debug.hpp"
namespace BEbraEngine {
    Texture::~Texture()
    {
        vkFreeMemory(VulkanRender::device, memory, 0);
        vkDestroyImage(VulkanRender::device, self, 0);
        vkDestroyImageView(VulkanRender::device, imageView, 0);
        vkDestroySampler(VulkanRender::device, sampler, 0);

    }
}