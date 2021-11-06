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
        transform->UpdatePosition(position, Vector4(0.f));
        ResetState();

    }

    void RigidBody::applyImpulse(const Vector3& force, const Vector3& direction)
    {
        body->applyImpulse(force, direction);
    }

    RigidBody::RigidBody()
    {
    }

    RigidBody::~RigidBody()
    {
        physics->removeRigidBody(body);
    }
}