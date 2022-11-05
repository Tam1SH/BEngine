module;
#include <Physics/btBulletDynamicsCommon.h>
#include <Physics/BulletDynamics/Dynamics/btRigidBody.h>

export module ColliderFactory;
import <optional>;
import Collider;
import OnlyMovable;
using std::optional;

namespace BEbraEngine {
	export class Physics;
}


namespace BEbraEngine {
	

	export class ColliderFactory
	{
	public:

		optional<Collider*> create(const ColliderCreateInfo& info);

		void destroyCollider(Collider& col);

		void setShape(Collider& collider, btCollisionShape& newShape);

		optional<btCollisionShape*> getShape(ColliderType type);

		ColliderFactory(ColliderFactory&& o) noexcept = default;
		ColliderFactory& operator=(ColliderFactory&& o) noexcept = default;

		ColliderFactory(const ColliderFactory& o) = delete;
		ColliderFactory& operator=(const ColliderFactory& o) = delete;

		ColliderFactory(Physics& physics) noexcept;
		~ColliderFactory() noexcept {}
	private:
		Physics* physics;
	};
	static_assert(OnlyMovable<ColliderFactory>);

}