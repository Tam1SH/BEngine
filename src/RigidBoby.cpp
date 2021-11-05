#include "stdafx.h"
#include "RigidBoby.hpp"
#include "Transform.hpp"
#include "Physics.hpp"
#include "Vector3.hpp"
namespace BEbraEngine {
    Physics* RigidBody::physics;

    void RigidBody::ResetState()
    {
        auto vec = transform->GetPosition();
        auto btvec = btVector3(
            vec.x, vec.y, vec.z
        );
        body->clearForces();
        body->clearGravity();
        body->getWorldTransform().setOrigin(btvec);
    }

    void RigidBody::SetPhysics(Physics* physics)
    {
        RigidBody::physics = physics;
    }

    void RigidBody::SetTransform(std::shared_ptr<Transform> transform)
    {
        this->transform = transform;
    }

    void RigidBody::SetShape(btCollisionShape* newShape)
    {

    }

    void RigidBody::SetDynamic(bool isActive)
    {
        if (!isActive) {
            body->setLinearFactor(btVector3(0, 0, 0));
            body->setAngularFactor(btVector3(0, 0, 0));
        }
        else {
            body->setLinearFactor(linearFactor);
            body->setAngularFactor(AngularFactor);
        }
    }


    void RigidBody::SetPosition(const Vector3& position)
    {
        transform->UpdatePosition(position);
        ResetState();

    }

    RigidBody::RigidBody()
    {
        auto shape = new btSphereShape(btScalar(1.));
        linearFactor = btVector3(1, 1, 1);
        AngularFactor = btVector3(1, 1, 1);
        btScalar mass(1.f);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            shape->calculateLocalInertia(mass, localInertia);
        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(btVector3(0, 0, 0));

        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
        body = new btRigidBody(rbInfo);

        name = "RigidBody";
        physics->addRigidBody(body);
    }

    RigidBody::~RigidBody()
    {
        physics->removeRigidBody(body);
    }
}