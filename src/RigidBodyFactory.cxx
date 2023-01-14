#include "platform.hpp"
#include <Physics/BulletDynamics/Dynamics/btRigidBody.h>
#include <Physics/btBulletDynamicsCommon.h>

module RigidBodyFactory;
import Collider;
import Physics;
import Exceptions;
import <stdexcept>;
namespace BEbraEngine {

	RigidBodyFactory::RigidBodyFactory(Physics& physics) noexcept
	{
		this->physics = &physics;
	}

    std::optional<RigidBody*> RigidBodyFactory::create(const RigidBodyCreateInfo& info)
	{
        if (!info.collider) {
            throw EmptyValueException();
        }

        RigidBody* rigidBody = new RigidBody();
        btCollisionObject* shape{};
        
        shape = &info.collider->get();

        info.collider->setRigidBody(*rigidBody);
        rigidBody->linearFactor = btVector3(1, 1, 1);
        rigidBody->AngularFactor = btVector3(1, 1, 1);
        rigidBody->collider = info.collider;
        btScalar mass(1.f);
        btVector3 localInertia(0, 0, 0);

        btTransform startTransform;
        startTransform.setIdentity();
        auto position = btVector3(info.position.x, info.position.y, info.position.z);
        startTransform.setOrigin(position);

        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        shape->getCollisionShape()->calculateLocalInertia(mass, localInertia);

        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape->getCollisionShape(), localInertia);
        rigidBody->body = std::make_unique<btRigidBody>(rbInfo);

        rigidBody->getRigidBody().setCollisionShape(shape->getCollisionShape());

        rigidBody->setName("RigidBody");
        rigidBody->body->activate();
        return std::optional<RigidBody*>(rigidBody);
	}

    void RigidBodyFactory::destroy(RigidBody& body)
    {
    }

    void RigidBodyFactory::setCollder(RigidBody& body, Collider& collider)
    {
        body.collider = &collider;
    }

    Collider& RigidBodyFactory::getCollider(RigidBody& body)
    {
        return *body.collider;
    }
}

