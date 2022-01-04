#pragma once
#include "stdafx.h"
#include "Collider.hpp"

class btCollisionShape;

namespace std {
	template<class T>
	class shared_ptr;
}

namespace BEbraEngine {
	class Physics;
}

namespace BEbraEngine {
	class ColliderFactory
	{
	public:
		ColliderFactory(Physics* physics);

		std::optional<Collider*> create(const Collider::ColliderCreateInfo& info);

		void destroyCollider(Collider* col);

		void setShape(Collider* collider, btCollisionShape* newShape);
	private:
		Physics* physics;
	};
}

