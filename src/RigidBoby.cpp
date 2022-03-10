#include "stdafx.h"

#include "RigidBoby.hpp"
#include "Transform.hpp"
#include "Physics.hpp"
#include "Vector3.hpp"
#include <Physics/btBulletCollisionCommon.h>
#include "IVisitorGameComponentDestroyer.hpp"
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

    /// <summary>  
    /// Обнуляется линейный и угловой фактор(Factor)
    /// </summary>
    void RigidBody::setDynamic(bool isActive) noexcept
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

    void RigidBody::applyImpulse(const Vector3& force, const Vector3& direction) noexcept
    {
        body->applyImpulse(force, direction);
        
    }

    void RigidBody::applyImpulseToPoint(float force, const Vector3& point) noexcept
    {
        auto posBody = transform->getPosition();
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
}