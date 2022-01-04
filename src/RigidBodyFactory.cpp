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
    std::optional<RigidBody*> RigidBodyFactory::create(const RigidBody::RigidBodyCreateInfo& info)
	{
        auto rigidBody = new RigidBody();
        btCollisionObject* shape{};
        if (info.collider) {
            shape = info.collider->get();
        }
        rigidBody->linearFactor = btVector3(1, 1, 1);
        rigidBody->AngularFactor = btVector3(1, 1, 1);

        btScalar mass(1.f);
        btVector3 localInertia(0, 0, 0);
        /*
        
        btScalar mass(1.f);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            shape->getCollisionShape()->calculateLocalInertia(mass, localInertia);
            */
        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(info.position);

        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        if (shape) {
            shape->getCollisionShape()->calculateLocalInertia(mass, localInertia);

            btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape->getCollisionShape(), localInertia);
            rigidBody->body = std::make_unique<btRigidBody>(rbInfo);
        }
        else {
            btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, 0, localInertia);
            rigidBody->body = std::make_unique<btRigidBody>(rbInfo);
        }

        rigidBody->setName("RigidBody");

        return std::optional<RigidBody*>(rigidBody);
	}
    void RigidBodyFactory::destroy(RigidBody* body)
    {
        if (body)
        {
#ifdef _DEBUG
            body->isDestroyed = true;
#endif // _DEBUG
        }
    }
    void RigidBodyFactory::setCollder(RigidBody* body, Collider* collider)
    {
        body->collider = collider;
    }
    Collider* RigidBodyFactory::getCollider(RigidBody* body)
    {
        return body->collider;
    }
}

