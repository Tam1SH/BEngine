#pragma once
#include "stdafx.h"
#include "RigidBoby.hpp"


using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace BEbraEngine {
	class Physics;
	class Collider;
}


namespace BEbraEngine {
	class RigidBodyFactory
	{
	public:
		RigidBodyFactory(Physics* physics);

		std::optional<RigidBody*> create(const RigidBody::RigidBodyCreateInfo& info);

		void destroy(RigidBody* body);

		void setCollder(RigidBody* body, Collider* collider);

		Collider* getCollider(RigidBody* body);
	private:
		Physics* physics;
	};
}
