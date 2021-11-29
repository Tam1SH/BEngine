#include "stdafx.h"
#include "RigidBodyFactory.hpp"
#include "Vector3.hpp"
#include "Physics.hpp"
#include "Collider.hpp"
namespace BEbraEngine {
	RigidBodyFactory::RigidBodyFactory(Physics* physics)
	{
		this->physics = physics;
	}
    RigidBody* RigidBodyFactory::create(Collider* collider)
	{
        auto rigidBody = new RigidBody();
        Collider* shape;
        if (!collider) {
            ColliderInfo info{};
            shape = physics->getColliderFactory()->create(&info);
        }
        else
            shape = collider;

        rigidBody->linearFactor = btVector3(1, 1, 1);
        rigidBody->AngularFactor = btVector3(1, 1, 1);
        btScalar mass(1.f);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            shape->get()->getCollisionShape()->calculateLocalInertia(mass, localInertia);
        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(btVector3(0, 0, 0));

        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape->get()->getCollisionShape(), localInertia);
        rigidBody->body = new btRigidBody(rbInfo);

        rigidBody->setName("RigidBody");

        return rigidBody;
	}
}

