export module Transform;
import GameComponent;
import Matrix4;
import BEbraMath;
import Vector3;
import Quaternion;

namespace BEbraEngine {
    struct TransformFactory;
}

namespace BEbraEngine {

    export struct Transform : GameComponent {

        friend struct TransformFactory;

        struct CreateInfo {

            Vector3 position{};
            Vector3 scale{ 1 };
            //Quartion quat;
        };

        template<typename Destroyer>
        void destroy(Destroyer& destroyer) {
            destroyer.destroyTransformComponent(*this);
        }

        void setPosition(const Vector3& position) noexcept;

        void setScale(const Vector3& scale) noexcept;

        void setRotation(const Quaternion& quat) noexcept;

        Vector3 getPosition() const noexcept;

        Quaternion getRotation() const noexcept;

        Matrix4 getBasis() const noexcept;

        ~Transform() { }

    private:

        Transform(const Vector3& position);

        Quaternion quat{};

        Vector3 position{};

        Vector3 scale{};

    };


}