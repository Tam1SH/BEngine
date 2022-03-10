#include "stdafx.h"
#include "ColliderFactory.hpp"
#include <Physics/btBulletCollisionCommon.h>
#include "Collider.hpp"
#include "Physics.hpp"
#include "RigidBoby.hpp"
namespace BEbraEngine {

	ColliderFactory::ColliderFactory(Physics* physics) {
		if (physics)
			this->physics = physics;
		else
			throw std::exception();
	}

	optional<Collider*> ColliderFactory::create(const Collider::ColliderCreateInfo& info)
	{
		auto col = new Collider();
		btCollisionShape* shape;

		col->_collider = unique_ptr<btCollisionObject>(new btCollisionObject());

		shape = getShape(info.type);

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
		if(collider._collider->getCollisionShape())
			delete collider._collider->getCollisionShape();
		if(collider.body)
			collider.body->getRigidBody().setCollisionShape(&newShape);
		collider._collider->setCollisionShape(&newShape);
	}

	btCollisionShape* ColliderFactory::getShape(Collider::Type type)
	{
		switch (type)
		{
		case Collider::Type::Box:
			return new btBoxShape(btVector3(1, 1, 1));
			break;
		case Collider::Type::Sphere:
			return new btSphereShape(1);
			break;
		case Collider::Type::Capsule:
			return new btCapsuleShape(1, 1);
			break;
		case Collider::Type::Cylinder:
			return new btCylinderShape(btVector3(1, 1, 1));
			break;
		case Collider::Type::Cone:
			return new btConeShape(1, 1);
			break;
		case Collider::Type::Mesh:
			throw std::runtime_error("not implemented xyu");
			break;
		default:
			break;
		}
	}

}