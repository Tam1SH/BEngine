#pragma once
#include "stdafx.h"
#include "platform.hpp"
#include "RigidBoby.hpp"

using BE_STD::optional;

namespace BEbraEngine {
	class Physics;
	class Collider;
}


namespace BEbraEngine {
	class RigidBodyFactory
	{
	public:
		RigidBodyFactory(Physics& physics);

		optional<RigidBody*> create(const RigidBody::CreateInfo& info);

		void destroy(RigidBody& body);

		void setCollder(RigidBody& body, Collider& collider);

		Collider& getCollider(RigidBody& body);
	private:
		Physics* physics;
	};
}