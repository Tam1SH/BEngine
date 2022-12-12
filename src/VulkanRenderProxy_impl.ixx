#include <vulkan.h>
#include <memory>

export module VulkanRenderProxy_impl;
import VulkanRenderProxy;
import VulkanRender;
import VulkanWindow;

using std::shared_ptr;


namespace BEbraEngine {

    VulkanRenderProxy::VulkanRenderProxy(VulkanRender&& render) : render(std::move(render))
    {
    }
    void VulkanRenderProxy::update()
    {
        render.update();
    }

    void VulkanRenderProxy::prepareDraw()
    {
        render.prepareDraw();
    }

    void VulkanRenderProxy::drawFrame()
    {
        render.drawFrame();
    }

    void VulkanRenderProxy::updateState(RenderData& data)
    {
        render.updateState(data);
    }

    void VulkanRenderProxy::create(VulkanWindow& window)
    {
        render.create(window);
    }

    void VulkanRenderProxy::destroyBuffer(RenderBuffer* buffer)
    {
        render.destroyBuffer(buffer);
    }

    RenderBuffer* VulkanRenderProxy::createUniformBuffer(uint32_t size)
    {
        return render.createUniformBuffer(size);
    }

    RenderBuffer* VulkanRenderProxy::createStorageBuffer(uint32_t size)
    {
        return render.createStorageBuffer(size);
    }

    RenderBuffer* VulkanRenderProxy::createIndexBuffer(std::vector<uint32_t> indices)
    {
        return render.createIndexBuffer(indices);
    }

    RenderBuffer* VulkanRenderProxy::createVertexBuffer(std::vector<Vertex> vertices)
    {
        return render.createVertexBuffer(vertices);
    }

    void VulkanRenderProxy::drawLine(const Vector3& from, const Vector3& to, const Vector3& color)
    {
        render.drawLine(from, to, color);
    }

    Vector2 VulkanRenderProxy::getCurrentRenderResolution()
    {
        return render.getCurrentRenderResolution();
    }

    uint32_t VulkanRenderProxy::alignmentBuffer(uint32_t originalSize, TypeRenderBuffer type)
    {
        return render.alignmentBuffer(originalSize, type);
    }

    VkDescriptorSet VulkanRenderProxy::createDescriptor(const VulkanDescriptorSetInfo& info)
    {
        return render.createDescriptor(info);
    }

    void VulkanRenderProxy::updateDesriptor(VkDescriptorSet& set, VulkanDescriptorSetInfo* info)
    {
        render.updateDesriptor(set, info);
    }

    VkDescriptorSet VulkanRenderProxy::createDescriptor(LightDescriptorInfo* info)
    {
        return render.createDescriptor(info);
    }

    VkDescriptorSet VulkanRenderProxy::createDescriptor2(RenderBufferView* buffer)
    {
        return render.createDescriptor2(buffer);
    }

    VkDescriptorSet VulkanRenderProxy::createDescriptor(RenderBuffer* buffer)
    {
        return render.createDescriptor(buffer);
    }

    void VulkanRenderProxy::freeDescriptor(VulkanRenderObject& set)
    {
        render.freeDescriptor(set);
    }

    void VulkanRenderProxy::freeDescriptor(VulkanDirLight* set)
    {
        render.freeDescriptor(set);
    }

    void VulkanRenderProxy::freeDescriptor(VulkanPointLight* set)
    {
        render.freeDescriptor(set);
    }

    void VulkanRenderProxy::destroyTextureAsync(shared_ptr<VulkanTexture> texture)
    {
        render.destroyTextureAsync(texture);
    }

    RenderBuffer* VulkanRenderProxy::createBufferAsync(void* data, uint32_t size, VkBufferUsageFlags usage)
    {
        return render.createBufferAsync(data, size, usage);
    }

    void VulkanRenderProxy::generateMipmaps(VulkanTexture* texture, VkFormat imageFormat, CommandBuffer& buffer)
    {
        render.generateMipmaps(texture, imageFormat, buffer);
    }

    void VulkanRenderProxy::createVkImage(unsigned char* data, VulkanTexture* texture, VkDeviceSize imageSize)
    {
        render.createVkImage(data, texture, imageSize);
    }

    VkImageView VulkanRenderProxy::createImageView(VulkanTexture* texture, VkFormat format, VkImageAspectFlags aspectFlags)
    {
        return render.createImageView(texture, format, aspectFlags);
    }

    void VulkanRenderProxy::createTextureSampler(VulkanTexture* texture)
    {
        render.createTextureSampler(texture);
    }

    VulkanTexture* VulkanRenderProxy::getBitMapFromSwapChainImage()
    {
        return render.getBitMapFromSwapChainImage();
    }

    void VulkanRenderProxy::recreateSwapChain(uint32_t width, uint32_t height)
    {
        render.recreateSwapChain(width, height);
    }

    VulkanRender& VulkanRenderProxy::get()
    {
        return render;
    }

}