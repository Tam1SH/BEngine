#include "stdafx.h"
#include "ColliderFactory.hpp"
namespace BEbraEngine {
	ColliderFactory::ColliderFactory(Physics* physics) {
		this->physics = physics;
	}

	Collider* ColliderFactory::create(ColliderInfo* info)
	{
		auto col = new Collider();
		col->_collider = std::unique_ptr<btCollisionObject>(new btCollisionObject());
		btCollisionShape* shape = new btBoxShape(Vector3(1.));
		setShape(col, shape);
		col->setSize(info->scale);
		return col;
	}

	void ColliderFactory::setShape(Collider* collider, btCollisionShape* newShape)
	{
		delete collider->_collider->getCollisionShape();
		collider->_collider->setCollisionShape(newShape);
	}

}