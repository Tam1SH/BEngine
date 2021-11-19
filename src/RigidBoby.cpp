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

    void RigidBody::setDynamic(bool isActive)
    {
        this->isActive = isActive;
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
    void RigidBody::applyImpulseToPoint(float force, const Vector3& point)
    {
        auto posBody = transform->GetPosition();
        float dist = sqrt(
            (posBody.x - point.x) * (posBody.x - point.x) +
            (posBody.y - point.y) * (posBody.y - point.y) +
            (posBody.z - point.z) * (posBody.z - point.z) 
        );
        
        body->applyCentralImpulse((point - posBody) / dist);
       // float force = 10.0f;   //but any value that works for you
        //Vector3 dir = glm::normalize(cam.origin + cam.direction) * force; //suppose your camera moves around
       // body->applyCentralImpulse(force * dist);

    }

    RigidBody::RigidBody()
    {
    }

    RigidBody::~RigidBody()
    {
    }
}