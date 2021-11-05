#pragma once
#include "AbstractComponent.hpp"
#include "btBulletDynamicsCommon.h"
#include <memory>
namespace BEbraEngine {
	class Transform;
	class Physics;
	class Vector3;

}

namespace BEbraEngine {

	class RigidBody : public GameObjectComponent
	{
	private:

		friend class Physics;

		static Physics* physics;

		btRigidBody* body;

		std::shared_ptr<Transform> transform;

		btVector3 linearFactor;

		btVector3 AngularFactor;

		void ResetState();

	public:

		btRigidBody* GetRigidBody() {
			return body;
		}
		static void SetPhysics(Physics* physics);

		void SetTransform(std::shared_ptr<Transform> transform);

		void SetShape(btCollisionShape* newShape);

		void SetDynamic(bool isActive);

		void SetPosition(const Vector3& position);

		void applyImpulse(const Vector3& force, const Vector3& direction);

		RigidBody();

		~RigidBody();

	};
}

