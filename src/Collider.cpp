#include "stdafx.h"
#include "Collider.hpp"
#include <Physics/btBulletCollisionCommon.h>
namespace BEbraEngine {
	void Collider::setScale(const Vector3& size)
	{
		this->size = size;
		_collider->getCollisionShape()->setLocalScaling(size);
	}
	void Collider::setPosition(const Vector3& size)
	{
		btTransform trans;
		trans.setOrigin(size);
		_collider->setWorldTransform(trans);
	}
	Vector3 Collider::getPosition()
	{
		return _collider->getWorldTransform().getOrigin();
	}
}

