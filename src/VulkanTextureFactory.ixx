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
import TextureFactory;
import <string>;

namespace BEbraEngine {
    export struct VulkanTextureFactory : public TextureFactory {

        Task<optional<Material*>> createMaterialAsync(const MaterialCreateInfo& info) override;

        Task<optional<Texture*>> createAsync(const CreateTextureInfo& info) override;

        optional<Texture*> createEmpty() override;

        void destroyTextureAsync(shared_ptr<Texture> texture) override;

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