#pragma once
#include "stdafx.h"
#include "GameComponent.hpp"
#include <Physics/btBulletDynamicsCommon.h>
#include "Debug.hpp"
#include "Vector3.hpp"

using std::shared_ptr;

namespace BEbraEngine {
	class Transform;
	class Physics;
	class Collider;
}

namespace BEbraEngine {

	class RigidBody : public GameComponent { DEBUG_DESTROY_CHECK_DECL()
	public:
		friend class RigidBodyFactory;

		struct RigidBodyCreateInfo {
			Collider* collider{};
			Vector3 position{};
			float mass{};
		};
	public:

		void destroy(IVisitorGameComponentDestroyer* destroyer) override;

		void resetState();

		btRigidBody* getRigidBody() { return body.get(); }

		void setTransform(Transform* transform);

		void setMass(float mass);

		void setDynamic(bool isActive);

		bool& getDynamic() { return isActive; }

		void setPosition(const Vector3& position);

		void applyImpulse(const Vector3& force, const Vector3& direction);

		void applyImpulseToPoint(float force, const Vector3& point);

		Transform* getTransform() { return transform; }

		RigidBody();

		~RigidBody();

	private:

		std::unique_ptr<btRigidBody> body;

		Collider* collider;

		Transform* transform;

		btVector3 linearFactor;

		btVector3 AngularFactor;


		bool isActive = true;
	

	};
}

