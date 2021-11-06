#pragma once
#include "AbstractComponent.hpp"
#include <vulkan/vulkan.h>
#include "Vector3.hpp"
#include "matrix.hpp"
#include "RenderBuffer.hpp"
#include <glm/gtx/quaternion.hpp>
namespace BEbraEngine {
    class TransformFactory;

}
namespace BEbraEngine {

    class Transform : public GameObjectComponent {
    private:
        friend class TransformFactory;

        friend class VulkanRenderObjectFactory;

        static TransformFactory* factory;

    private:

        glm::quat quartion;

        Vector3 position;

        Vector3 scale;

        Vector3 rotation;
    
        Matrix4 getBasis;
    private:

        static void SetFactory(TransformFactory* factory) noexcept;



    public:

        Matrix4 getMatrix();

        Transform(const Vector3& position);

        std::shared_ptr<RenderBufferView> buffer;

        static Transform* New(const Vector3& position = Vector3(0));

        void UpdatePosition(const Vector3& position, const Vector4& quat);

        void SetPosition(const Vector3& position) noexcept;

        void SetScale(const Vector3& scale) noexcept;

        Vector3 GetPosition() const noexcept;

        ~Transform() { };
    };
}