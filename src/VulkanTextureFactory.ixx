module;
#include <variant>

#include <optional>
#include <functional>
#include <memory>
#include <string>
export module VulkanTextureFactory;
import VulkanRender;
import Material;
import CRender;
import Render;
import Task;
import BitMap;
import Texture;
import OnlyMovable;

using std::shared_ptr;
using std::function;
using std::optional;

namespace BEbraEngine {
    export class VulkanTextureFactory {
    public:

        Task<optional<Material*>> createMaterialAsync(const MaterialCreateInfo& info);

        Task<optional<Texture*>> createAsync(const std::string& path);

        Texture* create(const std::string& path, bool generateMip);

        Texture* createEmpty();

        void saveImage(const char* fileName, int width, int height, int channel_num, const void* rows, int quality);
        
        void saveImage(const char* fileName, int width, int height, int channel_num, BEbraEngine::BitMap& bitMap, int quality);

       // void setDestroyer(VisitorGameComponentDestroyer& destroyer); //override;

        void destroyTexture(Texture& texture);

        void destroyTextureAsync(shared_ptr<Texture> texture);

        VulkanTextureFactory(VulkanRender& render);
        VulkanTextureFactory() {}

        VulkanTextureFactory(const VulkanTextureFactory&) = delete;
        VulkanTextureFactory& operator=(const VulkanTextureFactory&) = delete;

        VulkanTextureFactory(VulkanTextureFactory&&) noexcept = default;
        VulkanTextureFactory& operator=(VulkanTextureFactory&&) noexcept = default;

    private:
        VulkanRender* render;
        //VisitorGameComponentDestroyer* destroyer;

    };
    static_assert(OnlyMovable<VulkanTextureFactory>);

    namespace create {

        export std::variant<VulkanTextureFactory> textureFactory(Render& render) {

            return std::visit([](VulkanRender& render) {
                return std::variant<VulkanTextureFactory>(render);
            }, render);
        }
    }
}

module :private;
import CTextureFactory;

namespace BEbraEngine {
    static_assert(CTextureFactory<VulkanTextureFactory>);
}