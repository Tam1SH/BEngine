#include "platform.hpp"

export module RigidBodyFactory;
import <optional>;
import RigidBody;
using std::optional;


namespace BEbraEngine {
	export class Physics;
}


namespace BEbraEngine {

	export class RigidBodyFactory
	{
	public:
		RigidBodyFactory(Physics& physics);

		optional<RigidBody*> create(const RigidBodyCreateInfo& info);

		void destroy(RigidBody& body);

		void setCollder(RigidBody& body, Collider& collider);

		Collider& getCollider(RigidBody& body);
	private:
		Physics* physics;
	};
}
