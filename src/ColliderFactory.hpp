#pragma once
#include "CreateInfoStructures.hpp"
class btCollisionShape;

namespace BEbraEngine {
	class Physics;
	class Collider;
}

namespace BEbraEngine {
	class ColliderFactory
	{
	public:
		ColliderFactory(Physics* physics);

		Collider* create(ColliderInfo* info);

		void setShape(Collider* collider, btCollisionShape* newShape);
	private:
		Physics* physics;
	};
}

