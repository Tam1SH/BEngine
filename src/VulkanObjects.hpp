
#include "RenderObject.hpp"
#include "Camera.hpp"

namespace BEbraEngine {
    class VulkanRenderObject : public RenderObject {

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
    class VulkanCamera : public Camera {
    public:
        VulkanCamera(const Vector2& size, const Vector3& position) : Camera(size, position) {}

        VkDescriptorSet descriptor;

    };
}