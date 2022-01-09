
#include "RenderObject.hpp"
#include "Camera.hpp"

namespace BEbraEngine {
    class VulkanRenderObject final : public RenderObject {

    public:
        void release() override;

        ~VulkanRenderObject() {}

        void draw(VkCommandBuffer cmd);

        VkPipelineLayout* layout;

        VkDescriptorSet descriptor;
    };


    class VulkanPointLight : public PointLight {
    public:

        VkDescriptorSet descriptor;
    };

    class VulkanDirLight : public DirectionLight {
    public:

        VkDescriptorSet descriptor;
        ~VulkanDirLight() {}
    };
    class VulkanCamera : public SimpleCamera {
    public:
        VulkanCamera(const Vector2& size, const Vector3& position) : SimpleCamera(size, position) {}

        VkDescriptorSet descriptor;

    };
}