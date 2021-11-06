#pragma once
#include "Collider.hpp"
#include "CreateInfoStructures.hpp"
namespace BEbraEngine {
	class Physics;
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

