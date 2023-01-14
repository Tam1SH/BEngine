module;
#include <Physics/BulletDynamics/Dynamics/btRigidBody.h>
export module RigidBody;
import BEbraMath;
import Vector3;
import Quaternion;
import Transform;
import GameComponent;
import PoolObject;
import <optional>;
import <memory>;
using std::shared_ptr;
using std::unique_ptr;
using std::optional;

namespace BEbraEngine {
    export struct Collider;
}

namespace BEbraEngine {

    export struct RigidBodyCreateInfo {
        Collider* collider{};
        Vector3 position{};
        float mass{};
    };

    export struct RigidBody : GameComponent, PoolObject<RigidBody>  {
    public:
        friend struct RigidBodyFactory;

        struct TransformSetInfo {
            optional<Transform*> old{};
            Transform* nevv;
        };
    public:


        template<typename Destroyer>
        void destroy(Destroyer& destroyer) {
            //destroyer.destroyLight(*this);
        }

        //void destroy(�VisitorComponentDestroyer auto& destroyer) {
        //	destroyer.destroyRigidBodyComponent(*this);
        //}
		void moveTo(const Vector3& point) noexcept;

		void lockRotateX(bool yesno);

		void lockRotateY(bool yesno);

		void lockRotateZ(bool yesno);

		void setMaxVelocity(float velocity);

		float getMaxVelocity();

		void resetState() noexcept;

        btRigidBody& getRigidBody() const noexcept;

		void setTransform(TransformSetInfo& transform) noexcept;

		void setMass(float mass) noexcept;

		Vector3 getVelocity() noexcept;

		Vector3 getDirection() noexcept;

		void setDynamic(bool isActive) noexcept;

		bool getDynamic() const noexcept { return isActive; }

		void setPosition(const Vector3& position) noexcept;

		void setRotation(const Quaternion& quat) noexcept;

		void applyExplosionImpulse(float force, float radius, const Vector3& point) noexcept;

		void applyImpulse(const Vector3& force, const Vector3& direction) noexcept;

		void applyImpulseToPoint(float force, const Vector3& point) noexcept;

		Transform& getTransform() const noexcept { return *transform; }

		

        RigidBody(const RigidBody& o) = delete;
        RigidBody& operator=(const RigidBody& o) = delete;

        RigidBody() noexcept;
        ~RigidBody() noexcept;
	private:


        unique_ptr<btRigidBody> body;

        float maxVelocity{ 200 };

        Collider* collider{};

        Transform* transform{};

        Vector3 linearFactor{};

        Vector3 AngularFactor{};

        bool isActive = true;

    };
}