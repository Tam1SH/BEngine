module PhysicsProxy;
import RigidBody;
import Collider;
#include "PhysicsImpl.hpp"


namespace BEbraEngine {

	std::unique_ptr<Physics> createPhysicsImpl()
	{
		return std::make_unique<PhysicsImpl>();
	}

	optional<Collider*> PhysicsProxy::getObjectRayCast(const Vector3& start, Vector3& end)
	{
		return impl->getObjectRayCast(start, end);
	}

	void PhysicsProxy::update()
	{

		impl->update();
	}

	void PhysicsProxy::addRigidBody(RigidBody& body)
	{
		impl->addRigidBody(body);
	}

	void PhysicsProxy::removeRigidBody(RigidBody& body)
	{
		impl->removeRigidBody(body);
	}

	void PhysicsProxy::removeCollider(Collider& col)
	{
		impl->removeCollider(col);
	}

	void PhysicsProxy::debugDraw()
	{
		impl->debugDraw();
	}

	void PhysicsProxy::setCollder(RigidBody& body, Collider& collider)
	{
		impl->setCollder(body, collider);
	}
}