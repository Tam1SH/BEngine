#include "stdafx.h"
#include "ColliderFactory.hpp"
#include <Physics/btBulletCollisionCommon.h>
#include "Collider.hpp"
#include "Physics.hpp"
namespace BEbraEngine {
	ColliderFactory::ColliderFactory(Physics* physics) {
		this->physics = physics;
	}

	optional<Collider*> ColliderFactory::create(const Collider::ColliderCreateInfo& info)
	{
		auto col = new Collider();
		btCollisionShape* shape;
		col->_collider = unique_ptr<btCollisionObject>(new btCollisionObject());
		if (static_cast<glm::vec3>(info.position) == static_cast<glm::vec3>(Vector3(0, 0, 0)))
			shape = new btBoxShape(Vector3(1.));
		else 
			shape = new btBoxShape(Vector3(1.));

		setShape(*col, *shape);
		col->setScale(info.scale);
		col->setPosition(info.position);
		return optional<Collider*>(col);
	}

	void ColliderFactory::destroyCollider(Collider& col)
	{
#ifdef _DEBUG
		col.isDestroyed = true;
#endif 
	}

	void ColliderFactory::setShape(Collider& collider, btCollisionShape& newShape)
	{
		delete collider._collider->getCollisionShape();
		collider._collider->setCollisionShape(&newShape);
	}

}