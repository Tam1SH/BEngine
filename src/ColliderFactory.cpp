#include "stdafx.h"
#include "ColliderFactory.hpp"
#include <Physics/btBulletCollisionCommon.h>
#include "Collider.hpp"
#include "Physics.hpp"
namespace BEbraEngine {
	ColliderFactory::ColliderFactory(Physics* physics) {
		this->physics = physics;
	}

	Collider* ColliderFactory::create(ColliderInfo* info)
	{
		auto col = new Collider();
		btCollisionShape* shape;
		col->_collider = std::unique_ptr<btCollisionObject>(new btCollisionObject());
		if (static_cast<glm::vec3>(info->position) == static_cast<glm::vec3>(Vector3(0, 0, 0)))
			shape = new btBoxShape(Vector3(1.));
		else 
			shape = new btBoxShape(Vector3(1.));

		setShape(col, shape);
		col->setScale(info->scale);
		return col;
	}

	void ColliderFactory::destroyCollider(std::shared_ptr<Collider> col)
	{
		physics->removeCollider(col);
		col.reset();
	}

	void ColliderFactory::setShape(Collider* collider, btCollisionShape* newShape)
	{
		delete collider->_collider->getCollisionShape();
		collider->_collider->setCollisionShape(newShape);
	}

}