#pragma once
#include "CreateInfoStructures.hpp"
class btCollisionShape;
namespace std {
	template<class T>
	class shared_ptr;
}
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

		void destroyCollider(std::shared_ptr<Collider> col);

		void setShape(Collider* collider, btCollisionShape* newShape);
	private:
		Physics* physics;
	};
}

