module;
#include <stdexcept>
#include <Physics/btBulletDynamicsCommon.h>
module ColliderFactory;
import Physics;
import utils;
import Exceptions;
import RigidBody;
import Logger;
import PoolObject;
import <memory>;
import <optional>;

using std::unique_ptr;
using std::optional;

namespace BEbraEngine {


	void ColliderFactory::setShape(Collider& collider, btCollisionShape& newShape)
	{
		//Logger::debug("Set new shape, at {}, {}", __FILE__, __LINE__);

		if (collider._collider->getCollisionShape() != &newShape)
		{
			delete collider._collider->getCollisionShape();
			collider.body->getRigidBody().setCollisionShape(&newShape);
			collider._collider->setCollisionShape(&newShape);
		}

	}

	optional<Collider*> ColliderFactory::create(const ColliderCreateInfo& info)
	{
		//Logger::debug("create new Collder with info: (scale = {}, {}, {}), (position = {}, {}, {}), (type = {})",
		//	info.scale.x, info.scale.y, info.scale.z,
		//	info.position.x, info.position.y, info.position.z,
		//	utils::toString(info.type));

		auto col = new Collider();
		btCollisionShape* shape{};
		col->_collider = unique_ptr<btCollisionObject>(new btCollisionObject());
		auto opt_shape = getShape(info.type);
		if (opt_shape.has_value()) {
			shape = opt_shape.value();
		}
		else {
			//Logger::error("info has no object at {}, {}", __FILE__, __LINE__);
			throw EmptyValueException();
		}

		col->_collider->setUserPointer(col);
		col->_collider->setCollisionShape(shape);
		col->setScale(info.scale);
		col->setPosition(info.position);
		return std::make_optional(col);
	}

	void ColliderFactory::destroyCollider(Collider& col)
	{
		//Logger::debug("destroy collider({}) at {}, {}", (void*)&col, __FILE__, __LINE__);

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
			throw std::runtime_error("not implemented");
			break;
		default:
			return std::nullopt;
		}
	}

	ColliderFactory::ColliderFactory(Physics& physics) noexcept
	{
		this->physics = &physics;

		PoolObject<Collider>::setDeleter([&](Collider& c) {
			destroyCollider(c);
		});
	}


}