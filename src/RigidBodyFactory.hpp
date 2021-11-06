#pragma once

#include "RigidBoby.hpp"

namespace BEbraEngine {
	class Physics;
	class Collider;
}


namespace BEbraEngine {
	class RigidBodyFactory
	{
	public:
		RigidBodyFactory(Physics* physics);

		RigidBody* create(Collider* collider);
	private:
		Physics* physics;
	};
}
