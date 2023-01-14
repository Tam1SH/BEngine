module;
#include <Physics/btBulletDynamicsCommon.h>
#include <Physics/BulletDynamics/Dynamics/btRigidBody.h>
export module Collider;
import <memory>;
import <exception>;
import Vector3;
import Quaternion;
import Concepts;
import GameComponent;
import Concepts;
import PoolObject;
using std::unique_ptr;

namespace BEbraEngine {
	export struct RigidBody;
}

namespace BEbraEngine {

	export enum struct ColliderType {
		Box,
		Sphere,
		Capsule,
		Cylinder,
		Cone,
		Mesh
	};

	export struct ColliderCreateInfo
	{
		Vector3 scale{};
		Vector3 position{};
		ColliderType type{};
	};

	export struct Collider : GameComponent, PoolObject<Collider> {

		friend struct ColliderFactory;

		template<typename Destroyer>
		void destroy(Destroyer& destroyer) {
			destroyer.destroyCollider(*this);
		}

		btCollisionObject& get() noexcept { return *_collider; }

		const btCollisionObject& get() const noexcept { return *_collider; }

		void setScale(const Vector3& size) noexcept;

		void setRotation(const Quaternion& quat) noexcept;

		Vector3& getSize() noexcept { return size; }

		const Vector3& getSize() const noexcept { return size; }

		void setPosition(const Vector3& position) noexcept;

		void setMass(float mass) noexcept;

		Vector3 getPosition() const noexcept;

		void setRigidBody(RigidBody& body);
		
		Collider(Collider&& o) noexcept = default;
		Collider& operator=(Collider&& o) noexcept = default;

		Collider(const Collider& o) = delete;
		Collider& operator=(const Collider& o) = delete;

		Collider() noexcept;
		~Collider() noexcept;


	public:
		RigidBody* body{};
		unique_ptr<btCollisionObject> _collider;
		Vector3 position{};
		Vector3 size{};
	};
	static_assert(OnlyMovable<Collider>);
	
}

