#include "stdafx.h"
#include "RigidBodyFactory.hpp"
#include "Vector3.hpp"
#include "Physics.hpp"
#include "Collider.hpp"
namespace BEbraEngine {

	RigidBodyFactory::RigidBodyFactory(Physics& physics)
	{
		this->physics = &physics;
	}

    optional<RigidBody*> RigidBodyFactory::create(const RigidBody::CreateInfo& info)
	{
        if (!info.collider) {
            throw std::runtime_error("invalid pointer collider");
        }
        auto rigidBody = new RigidBody();
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
        startTransform.setOrigin(info.position);

        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        shape->getCollisionShape()->calculateLocalInertia(mass, localInertia);

        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape->getCollisionShape(), localInertia);
        rigidBody->body = std::make_unique<btRigidBody>(rbInfo);

        rigidBody->getRigidBody().setCollisionShape(shape->getCollisionShape());

        rigidBody->setName("RigidBody");
        rigidBody->body->activate();
        return optional<RigidBody*>(rigidBody);
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

