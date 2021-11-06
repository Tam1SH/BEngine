#include "stdafx.h"
#include "RigidBodyFactory.hpp"
#include "Vector3.hpp"
#include "Physics.hpp"
namespace BEbraEngine {
	RigidBodyFactory::RigidBodyFactory(Physics* physics)
	{
		this->physics = physics;
	}
    RigidBody* RigidBodyFactory::create(Collider* collider)
	{
        auto rigidBody = new RigidBody();
        btCollisionObject* shape = collider->get();
        rigidBody->linearFactor = btVector3(1, 1, 1);
        rigidBody->AngularFactor = btVector3(1, 1, 1);
        btScalar mass(1.f);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            shape->getCollisionShape()->calculateLocalInertia(mass, localInertia);
        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(btVector3(0, 0, 0));

        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape->getCollisionShape(), localInertia);
        rigidBody->body = new btRigidBody(rbInfo);

        rigidBody->SetName("RigidBody");

        physics->addRigidBody(rigidBody->body);
        return rigidBody;
	}
}

