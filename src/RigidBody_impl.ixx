#include <Physics/BulletDynamics/Dynamics/btRigidBody.h>
export module RigidBody_impl;
import RigidBody;
import BEbraMath;

namespace BEbraEngine {

    void RigidBody::moveTo(const Vector3& point) noexcept
    {
        transform->setPosition(point);
        resetState();
    }

    void RigidBody::lockRotateX(bool yesno)
    {

        if (yesno) {
            AngularFactor.x = 0;
            body->setDamping(0.5, 0);
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
            AngularFactor.y = 0;
            body->setAngularFactor(AngularFactor);
        }
        else {
            body->setAngularFactor(AngularFactor);
        }
    }

    void RigidBody::lockRotateZ(bool yesno)
    {
        if (yesno) {
            AngularFactor.z = 0;
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



    void RigidBody::resetState() noexcept
    {

        body->clearForces();
        body->clearGravity();
        body->getWorldTransform().setOrigin(transform->getPosition());
        body->getWorldTransform().setRotation(transform->getRotation());
    }


    void RigidBody::setTransform(TransformSetInfo& info) noexcept
    {
        if (info.nevv)
            this->transform = info.nevv;
        //            else DEBUG_LOG3("info.nevv is null", this);
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

    bool RigidBody::getDynamic() const noexcept { return isActive; }

    void RigidBody::setPosition(const Vector3& position) noexcept
    {
        transform->setPosition(position);
        resetState();

    }

    void RigidBody::setRotation(const Quaternion& quat) noexcept {
        transform->setRotation(quat);
        resetState();
    }

    void RigidBody::applyExplosionImpulse(float force, float radius, const Vector3& point) noexcept
    {
        auto _point = btVector3(point.x, point.y, point.z);
        auto pos = transform->getPosition();

        Vector3 direction = BEbraMath::normalize(pos - point);

        if (BEbraMath::length(pos - point) < radius) {
            if (!body->isActive())
                body->activate(true);
            body->applyImpulse(direction * force, _point);
        }
    }

    void RigidBody::applyImpulse(const Vector3& force, const Vector3& direction) noexcept
    {
        body->activate();
        auto _force = btVector3(force.x, force.y, force.z);
        auto _direction = btVector3(direction.x, direction.y, direction.z);
        body->applyImpulse(_force, _direction);
    }

    void RigidBody::applyImpulseToPoint(float force, const Vector3& point) noexcept
    {
        auto posBody = transform->getPosition();
        float dist = BEbraMath::distance(posBody, point);
        body->activate();
        //body->applyCentralImpulse((point - posBody) / dist);


    }


    Transform& RigidBody::getTransform() const noexcept { return *transform; }

    RigidBody::~RigidBody()
    {
        //DEBUG_DESTROY_CHECK("RigidBody has not destroyed", this, "", Debug::ObjectType::RigidBody, Debug::MessageType::Info);
    }

    RigidBody::RigidBody() noexcept
    {
    }


}