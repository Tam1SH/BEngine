module;
export module VulkanTextureFactory;
import VulkanRender;
import Material;
import TextureData;
import TextureLoader;
import Task;
import BitMap;
import Texture;
import stdDeclaration;
import <string>;

namespace BEbraEngine {
    export struct VulkanTextureFactory {

        Task<optional<Material*>> createMaterialAsync(const MaterialCreateInfo& info);

        Task<optional<Texture*>> createAsync(const CreateTextureInfo& info);

        optional<Texture*> createEmpty();

        void destroyTextureAsync(shared_ptr<Texture> texture);

        VulkanTextureFactory(VulkanRender& render, TextureLoader& loader);
        VulkanTextureFactory() {}

        VulkanTextureFactory(const VulkanTextureFactory&) = delete;
        VulkanTextureFactory& operator=(const VulkanTextureFactory&) = delete;

        VulkanTextureFactory(VulkanTextureFactory&&) noexcept = default;
        VulkanTextureFactory& operator=(VulkanTextureFactory&&) noexcept = default;

    private:
        void createVkTexture(const TextureData& data, VulkanTexture* tex, size_t imageSize);

    private:
        VulkanRender* render;
        TextureLoader* loader;
    };
}