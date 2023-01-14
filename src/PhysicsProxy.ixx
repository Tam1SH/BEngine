export module PhysicsProxy;
import Physics;
import RigidBody;
import Vector3;
import <optional>;
import <memory>;
using std::optional;

namespace BEbraEngine {

	export struct PhysicsProxy : public Physics {

		optional<Collider*> getObjectRayCast(const Vector3& start, Vector3& end) override;

		void update() override;

		void addRigidBody(RigidBody& body) override;

		void removeRigidBody(RigidBody& body) override;

		void removeCollider(Collider& col) override;

		void debugDraw() override;

		void setCollder(RigidBody& body, Collider& collider) override;

		PhysicsProxy(std::unique_ptr<Physics> impl) : impl(std::move(impl)) {}

	private:
		std::unique_ptr<Physics> impl;
	};

	export std::unique_ptr<Physics> createPhysicsImpl();

}
