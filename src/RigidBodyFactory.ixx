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

		optional<RigidBody*> create(const RigidBodyCreateInfo& info);

		void destroy(RigidBody& body);

		void setCollder(RigidBody& body, Collider& collider);

		Collider& getCollider(RigidBody& body);

		RigidBodyFactory(Physics& physics) noexcept;
		~RigidBodyFactory() noexcept {}

		RigidBodyFactory(const RigidBodyFactory& o) = delete;
		RigidBodyFactory& operator=(const RigidBodyFactory& o) = delete;

		RigidBodyFactory(RigidBodyFactory&& o) noexcept = default;
		RigidBodyFactory& operator=(RigidBodyFactory&& o) noexcept = default;

	private:
		Physics* physics;
	};
}
