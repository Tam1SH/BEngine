#include <Physics/btBulletDynamicsCommon.h>
#include <Physics/BulletDynamics/Dynamics/btRigidBody.h>
export module Collider_impl;
import Collider;
//import GameComponentDestroyer;

namespace BEbraEngine {


	void Collider::setScale(const Vector3& size) noexcept
	{
		this->size = size;
		auto _size = btVector3(size.x, size.y, size.z);
		_collider->getCollisionShape()->setLocalScaling(_size);
	}

	void Collider::setRotation(const Quaternion& quat) noexcept {
		btTransform trans;
		trans.setRotation(static_cast<btQuaternion>(quat));
		trans.setOrigin(position.toVec<btVector3>());
		_collider->setWorldTransform(trans);
	}

	void Collider::setPosition(const Vector3& position) noexcept
	{
		btTransform trans;
		auto _position = btVector3(position.x, position.y, position.z);
		trans.setOrigin(_position);
		trans.setRotation(_collider->getWorldTransform().getRotation());
		_collider->setWorldTransform(trans);
	}

	void Collider::setMass(float mass) noexcept
	{
		auto vec = btVector3(0, 0, 0);
		_collider->getCollisionShape()->calculateLocalInertia(mass, vec);
	}

	Vector3 Collider::getPosition() const noexcept
	{
		return _collider->getWorldTransform().getOrigin();
	}

	void Collider::setRigidBody(RigidBody& body)
	{
		this->body = &body;
	}


	Collider::Collider() noexcept
	{
		name_ = "Collider";
	}

	Collider::~Collider() noexcept
	{
		//DEBUG_DESTROY_CHECK("Collider has not destroyed", this, "", Debug::ObjectType::Collider, Debug::MessageType::Info);
	}

}