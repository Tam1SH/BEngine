export module Transform;
import Matrix4;
import Debug;
import BEbraMath;
import Vector3;
import Quaternion;
import GameComponent;

namespace BEbraEngine {
    class TransformFactory;
    class IVisitorGameComponentDestroyer;
}
namespace BEbraEngine {

    export class Transform final : public GameComponent {
    public:
        friend class TransformFactory;

        struct CreateInfo {

            Vector3 position{};
            Vector3 scale{ 1 };
            //Quartion quat;
        };

    public:

        // void destroy(IVisitorGameComponentDestroyer& destroyer) {}//override;

         //void destroy(ÑVisitorGameComponentDestroyer auto& destroyer) {
         //    destroyer.destroyTransformComponent(*this);
         //}

        void setPosition(const Vector3& position) noexcept
        {
            this->position = position;
        }

        void setScale(const Vector3& scale) noexcept
        {
            this->scale = scale;
        }

        void setRotation(const Quaternion& quat) noexcept
        {
            this->quat = quat;
        }


        Vector3& getPosition() noexcept
        {
            return position;
        }
        const Vector3& getPosition() const noexcept
        {
            return position;
        }
        Quaternion getRotation() const noexcept
        {
            return quat;
        }

        Matrix4 getBasis() const noexcept
        {

            auto model = Matrix4(1);

            model = BEbraMath::translate(model, position);
            model = BEbraMath::scale(model, scale);

            model *= BEbraMath::toMat4(quat);

            return Matrix4(model);
        }

        ~Transform()
        {
        }

    private:

        Transform(const Vector3& position)
        {
            this->position = position;
            scale = Vector3(1);
        }

        Quaternion quat{};

        Vector3 position{};

        Vector3 scale{};



    };







    //void Transform::destroy(IVisitorGameComponentDestroyer& destroyer)
    //{
    //    destroyer.destroyTransformComponent(*this);
    //}






 




}