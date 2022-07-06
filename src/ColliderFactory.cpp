#include "platform.hpp"
#include <Physics/btBulletDynamicsCommon.h>
#include <Physics/BulletDynamics/Dynamics/btRigidBody.h>
#include <stdexcept>
#include "Physics.hpp"
module ColliderFactory;
import RigidBody;
import <memory>;
import <optional>;
using std::unique_ptr;
using std::optional;

namespace BEbraEngine {

	ColliderFactory::ColliderFactory(Physics& physics) {
		this->physics = &physics;
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

	optional<Collider*> ColliderFactory::create(const ColliderCreateInfo& info)
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
		//col.isDestroyed = true;
#endif 
		physics->removeCollider(col);
	}



	optional<btCollisionShape*> ColliderFactory::getShape(ColliderType type)
	{
		switch (type)
		{
		case ColliderType::Box:
			return optional<btCollisionShape*>(new btBoxShape(btVector3(1, 1, 1)));
			break;
		case ColliderType::Sphere:
			return optional<btCollisionShape*>(new btSphereShape(1));
			break;
		case ColliderType::Capsule:
			return optional<btCollisionShape*>(new btCapsuleShape(1, 1));
			break;
		case ColliderType::Cylinder:
			return optional<btCollisionShape*>(new btCylinderShape(btVector3(1, 1, 1)));
			break;
		case ColliderType::Cone:
			return optional<btCollisionShape*>(new btConeShape(1, 1));
			break;
		case ColliderType::Mesh:
			throw std::runtime_error("not implemented xyu");
			break;
		default:
			break;
		}
		return optional<btCollisionShape*>();
	}

}