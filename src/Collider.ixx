#include "platform.hpp"
#include <Physics/btBulletDynamicsCommon.h>

export module Collider;
import Debug;
import <memory>;
import <exception>;
import Vector3;
import Quaternion;
import Concepts;
import GameComponent;

using std::unique_ptr;


namespace BEbraEngine {
	export class RigidBody;
}

namespace BEbraEngine {

	export enum class ColliderType {
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

	export class Collider : public GameComponent {
		//DEBUG_DESTROY_CHECK_DECL()
	public:
		friend class ColliderFactory;
	public:

		template<typename T>
		void destroy(T& destroyer) {
			destroyer.destroyColliderComponent(*this);
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

		template<typename T>
		void as() {
			if (dynamic_cast<T*>(this))
				return static_cast<T*>(this);

			//throw std::runtime_error("object does not match of type");
		}
		

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

	//static_assert(OnlyMovable<Collider>);
	

	

}

