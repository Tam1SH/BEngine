#include "stdafx.h"

#include "RigidBoby.hpp"
#include "Transform.hpp"
#include "Physics.hpp"
#include "Vector3.hpp"
#include <Physics/btBulletCollisionCommon.h>
#include "IVisitorGameComponentDestroyer.hpp"
#include "Math.hpp"
namespace BEbraEngine {

    /// <summary>  
    /// Обнуляются сила и гравитация и объект перемещается в позицию, полученную из привязанного transform
    ///</summary>
    void RigidBody::resetState() noexcept
    {
        
        body->clearForces();
        body->clearGravity();
        body->getWorldTransform().setOrigin(transform->getPosition());
        body->getWorldTransform().setRotation(transform->getRotation());
    }

    /// <summary>  
    /// Устанавливается указатель на новый transform. Предыдущий должен быть переиспользован либо удалён.
    /// </summary>
    void RigidBody::setTransform(TransformSetInfo& info) noexcept
    {
        if (info.nevv)
            this->transform = info.nevv;
        else DEBUG_LOG3("info.nevv is null", this);
    }

    void RigidBody::setMass(float mass) noexcept
    {
    }

    Vector3 RigidBody::getVelocity() noexcept
    {
        return body->getLinearVelocity();
    }

    Vector3 RigidBody::getDirection() noexcept
    {
        return BEbraMath::normalize(body->getLinearVelocity());
    }

    /// <summary>  
    /// Обнуляется линейный и угловой фактор(Factor)
    /// </summary>
    void RigidBody::setDynamic(bool isActive) noexcept
    {
        this->isActive = isActive;
        if (this->isActive) {
            body->setLinearFactor(linearFactor);
            body->setAngularFactor(AngularFactor);
            body->setCollisionFlags(btCollisionObject::CollisionFlags::CF_DYNAMIC_OBJECT);
        }
        else {
            btCollisionObject::CollisionFlags;
            body->getCollisionFlags();
            body->setCollisionFlags(btCollisionObject::CollisionFlags::CF_STATIC_OBJECT);
            body->setLinearFactor(btVector3(0, 0, 0));
            body->setAngularFactor(btVector3(0, 0, 0));
        }
    }

    /// <summary>  
    ///  Устанавливается в текущую позицию, обновляется привязанный tranform и обнуляется состояние объекта.
    /// </summary>
    void RigidBody::setPosition(const Vector3& position) noexcept
    {
        transform->updatePosition(position);
        resetState();

    }
    void RigidBody::setRotation(const Quaternion& quat) noexcept {
        transform->setQuat(quat);
        resetState();
    }

    void RigidBody::applyExplosionImpulse(float force, float radius, const Vector3& point) noexcept
    {
        
        auto pos = transform->getPosition();
        
        Vector3 direction = BEbraMath::normalize(pos - point);
        
        if (BEbraMath::length(pos - point) < radius) {
            if(!body->isActive())
                body->activate();
            body->applyImpulse(direction * force, point);
            
            
        }
    }

    void RigidBody::applyImpulse(const Vector3& force, const Vector3& direction) noexcept
    {
        body->activate();

        body->applyImpulse(force, direction);
    }

    void RigidBody::applyImpulseToPoint(float force, const Vector3& point) noexcept
    {
        auto posBody = transform->getPosition();
        float dist = BEbraMath::distance(posBody, point);
        body->activate();
        body->applyCentralImpulse((point - posBody) / dist);
        
       // float force = 10.0f;   //but any value that works for you
        //Vector3 dir = glm::normalize(cam.origin + cam.direction) * force; //suppose your camera moves around
       // body->applyCentralImpulse(force * dist);

    }

    RigidBody::RigidBody() noexcept
    {
    }

    RigidBody::~RigidBody()
    {
        DEBUG_DESTROY_CHECK("RigidBody has not destroyed", this, "", Debug::ObjectType::RigidBody, Debug::MessageType::Info);
    }

    void RigidBody::destroy(IVisitorGameComponentDestroyer& destroyer)
    {
        destroyer.destroyRigidBodyComponent(*this);
    }
    void RigidBody::moveTo(const Vector3& point) noexcept
    {
        transform->setPosition(point);
        resetState();
    }
    void RigidBody::lockRotateX(bool yesno)
    {
        
        if (yesno) {
            AngularFactor.setX(0);
            //body->setDamping(0.5, 0);
            body->setFriction(5);
            body->setAngularFactor(AngularFactor);
        }
        else {
            body->setAngularFactor(AngularFactor);
        }
    }
    void RigidBody::lockRotateY(bool yesno)
    {
        if (yesno) {
            AngularFactor.setY(0);
            body->setAngularFactor(AngularFactor);
        }
        else {
            body->setAngularFactor(AngularFactor);
        }
    }
    void RigidBody::lockRotateZ(bool yesno)
    {
        if (yesno) {
            AngularFactor.setZ(0);
            body->setAngularFactor(AngularFactor);
        }
        else {
            body->setAngularFactor(AngularFactor);
        }
    }
    void RigidBody::setMaxVelocity(float velocity)
    {
        maxVelocity = velocity;
    }
    float RigidBody::getMaxVelocity()
    {
        return maxVelocity;
    }
}