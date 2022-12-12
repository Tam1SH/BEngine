#include <vector>
#include <memory>
#include <vulkan.h>
#include "CommandBuffer.hpp"
export module VulkanRenderProxy;
import Vertex;
import RenderBuffer;
import RenderData;
import Vector3;
import Vector2;
import VulkanRender;
import CreateInfoStructures;
import RenderAllocatorTypeRenderBuffer;
using std::shared_ptr;
using std::vector;

//Это даже не прокси.
export namespace BEbraEngine {
    struct VulkanRenderObject;
    struct VulkanDirLight;
    struct VulkanPointLight;
    struct VulkanWindow;
}

namespace BEbraEngine {
	export struct VulkanRenderProxy {

        void update();

        void prepareDraw();

        void drawFrame();

        void updateState(RenderData& data);

        void create(VulkanWindow& window);

        void destroyBuffer(RenderBuffer* buffer);

        RenderBuffer* createUniformBuffer(uint32_t size);

        RenderBuffer* createStorageBuffer(uint32_t size);

        RenderBuffer* createIndexBuffer(std::vector<uint32_t> indices);

        RenderBuffer* createVertexBuffer(std::vector<Vertex> vertices);

        void drawLine(const Vector3& from, const Vector3& to, const Vector3& color);

        Vector2 getCurrentRenderResolution();

        uint32_t alignmentBuffer(uint32_t originalSize, TypeRenderBuffer type);

        VkDescriptorSet createDescriptor(const VulkanDescriptorSetInfo& info);

        void updateDesriptor(VkDescriptorSet& set, VulkanDescriptorSetInfo* info);

        VkDescriptorSet createDescriptor(LightDescriptorInfo* info);

        VkDescriptorSet createDescriptor2(RenderBufferView* buffer);

        VkDescriptorSet createDescriptor(RenderBuffer* buffer);

        void freeDescriptor(VulkanRenderObject& set);

        void freeDescriptor(VulkanDirLight* set);

        void freeDescriptor(VulkanPointLight* set);

        void destroyTextureAsync(shared_ptr<VulkanTexture> texture);

        RenderBuffer* createBufferAsync(void* data, uint32_t size, VkBufferUsageFlags usage);

        void generateMipmaps(VulkanTexture* texture, VkFormat imageFormat, CommandBuffer& buffer);

        void createVkImage(unsigned char* data, VulkanTexture* texture, VkDeviceSize imageSize);

        VkImageView createImageView(VulkanTexture* texture, VkFormat format, VkImageAspectFlags aspectFlags);

        void createTextureSampler(VulkanTexture* texture);

        VulkanTexture* getBitMapFromSwapChainImage();

        void recreateSwapChain(uint32_t width, uint32_t height);

        VulkanRender& get();

        VulkanRenderProxy(VulkanRender&& render);
    private:
        VulkanRender&& render;
	};

}
