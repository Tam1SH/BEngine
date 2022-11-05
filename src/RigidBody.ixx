module;
#include "platform.hpp"
#include <Physics/BulletDynamics/Dynamics/btRigidBody.h>

export module RigidBody;
import Debug;
import BEbraMath;
import Vector3;
import Quaternion;
import Transform;
import GameComponent;

import <optional>;
import <memory>;

using std::shared_ptr;
using std::unique_ptr;
using std::optional;


namespace BEbraEngine {
    export class Physics;
    export class Collider;
    export struct GameComponentDestroyer;
}

namespace BEbraEngine {

    export struct RigidBodyCreateInfo {
        Collider* collider{};
        Vector3 position{};
        float mass{};
    };

    export class RigidBody : public GameComponent {
    public:
        friend class RigidBodyFactory;
        friend class Physics;

        struct TransformSetInfo {
            optional<Transform*> old{};
            Transform* nevv;
        };
    public:


        template<typename Destroyer>
        void destroy(Destroyer& destroyer) {
            //destroyer.destroyLight(*this);
        }

        //void destroy(ÑVisitorComponentDestroyer auto& destroyer) {
        //	destroyer.destroyRigidBodyComponent(*this);
        //}
		void moveTo(const Vector3& point) noexcept;

		void lockRotateX(bool yesno);

		void lockRotateY(bool yesno);

		void lockRotateZ(bool yesno);

		void setMaxVelocity(float velocity);

		float getMaxVelocity();

		void resetState() noexcept;

		btRigidBody& getRigidBody() const noexcept { return *body; }

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
        //TODO: ïåðåîïðåäåëèòü move êîíñòðóêòîð

        ~RigidBody() noexcept;
	private:

		RigidBody() noexcept;

        unique_ptr<btRigidBody> body;

        float maxVelocity{ 200 };

        Collider* collider{};

        Transform* transform{};

        Vector3 linearFactor{};

        Vector3 AngularFactor{};

        bool isActive = true;

    };
}