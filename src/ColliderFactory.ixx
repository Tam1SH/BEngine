#include "platform.hpp"
#include <Physics/btBulletDynamicsCommon.h>
#include <Physics/BulletDynamics/Dynamics/btRigidBody.h>

export module ColliderFactory;
import <optional>;
import Collider;
using std::optional;

namespace BEbraEngine {
	export class Physics;
}


namespace BEbraEngine {
	
	export class ColliderFactory
	{
	public:
		ColliderFactory(Physics& physics);

		optional<Collider*> create(const ColliderCreateInfo& info);

		void destroyCollider(Collider& col);

		void setShape(Collider& collider, btCollisionShape& newShape);

		optional<btCollisionShape*> getShape(ColliderType type);
	private:

		Physics* physics;
	};

}