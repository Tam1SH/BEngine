#pragma once
#include "GameComponent.hpp"
#include "Vector3.hpp"
#include "matrix.hpp"
#include <glm/gtx/quaternion.hpp>
#include "Debug.hpp"
#include "Quaternion.hpp"
namespace BEbraEngine {
    class TransformFactory;
    class IVisitorGameComponentDestroyer;
}
namespace BEbraEngine {

    class Transform final : public GameComponent {
    public:
        friend class TransformFactory;

        struct TransformCreateInfo {

            Vector3 position{};
            Vector3 scale{ 1 };
            //Quartion quat;
        };

    public:

        void destroy(IVisitorGameComponentDestroyer& destroyer) override;

        void updatePosition(const Vector3& position) noexcept;

        void setPosition(const Vector3& position) noexcept;

        void setScale(const Vector3& scale) noexcept;

        void setQuat(const Quaternion& quat) noexcept;


        Vector3 getPosition() const noexcept;

        Quaternion getRotation() const noexcept;

        Matrix4 getBasis() const noexcept;

        ~Transform();

    private:

        Transform(const Vector3& position);

        Quaternion quat{};

        Vector3 position{};

        Vector3 scale{};



    };
}