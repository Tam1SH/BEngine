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
    public:
        friend class TransformFactory;

    public:
        void updatePosition(const Vector3& position, const Vector4& quat);

        void setPosition(const Vector3& position) noexcept;

        void setScale(const Vector3& scale) noexcept;

        //void setRotation()

        Vector3 getPosition() const noexcept;

        Matrix4 getBasis() const noexcept;

        ~Transform();

    private:

        Transform(const Vector3& position);

        glm::quat quartion{};

        Vector3 position{};

        Vector3 scale{};

    };
}