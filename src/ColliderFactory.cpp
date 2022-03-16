#include "stdafx.h"
#include "ColliderFactory.hpp"
#include <Physics/btBulletCollisionCommon.h>
#include "Collider.hpp"
#include "Physics.hpp"
#include "RigidBoby.hpp"

namespace BEbraEngine {

	ColliderFactory::ColliderFactory(Physics& physics) {
		this->physics = &physics;
	}

	optional<Collider*> ColliderFactory::create(const Collider::CreateInfo& info)
	{
		auto col = new Collider();
		btCollisionShape* shape{};

		col->_collider = unique_ptr<btCollisionObject>(new btCollisionObject());
		auto opt_shape = getShape(info.type);
		if (opt_shape.has_value())
			shape = opt_shape.value();
		else throw std::exception();

		col->_collider->setUserPointer(col);
		col->_collider->setCollisionShape(shape);
		col->setScale(info.scale);
		col->setPosition(info.position);
		return optional<Collider*>(col);
	}

	void ColliderFactory::destroyCollider(Collider& col)
	{
#ifdef _DEBUG
		col.isDestroyed = true;
#endif 
		physics->removeCollider(col);
	}

	void ColliderFactory::setShape(Collider& collider, btCollisionShape& newShape)
	{
		if (collider._collider->getCollisionShape() != &newShape)
		{
			delete collider._collider->getCollisionShape();
			collider.body->getRigidBody().setCollisionShape(&newShape);
			collider._collider->setCollisionShape(&newShape);
		}

	}

	optional<btCollisionShape*> ColliderFactory::getShape(Collider::Type type)
	{
		switch (type)
		{
		case Collider::Type::Box:
			return optional<btCollisionShape*>(new btBoxShape(btVector3(1, 1, 1)));
			break;
		case Collider::Type::Sphere:
			return optional<btCollisionShape*>(new btSphereShape(1));
			break;
		case Collider::Type::Capsule:
			return optional<btCollisionShape*>(new btCapsuleShape(1, 1));
			break;
		case Collider::Type::Cylinder:
			return optional<btCollisionShape*>(new btCylinderShape(btVector3(1, 1, 1)));
			break;
		case Collider::Type::Cone:
			return optional<btCollisionShape*>(new btConeShape(1, 1));
			break;
		case Collider::Type::Mesh:
			throw std::runtime_error("not implemented xyu");
			break;
		default:
			break;
		}
		return optional<btCollisionShape*>();
	}

}