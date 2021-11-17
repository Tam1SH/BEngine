#include "stdafx.h"
#include "Physics.hpp"
#include "RigidBoby.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Time.hpp"
#include "Vector4.hpp"
//TODO: сделать так, чтобы физика параллельно обрабатывалась бл€ть(жаль производительность растЄт ниху€ не линейно). ѕерекомпилить с использованием TBB(пока только дл€ винды)
namespace BEbraEngine {


    void Physics::Update()
    {
        while (!queueAdd.empty()) {
            std::weak_ptr<RigidBody> wBody;
            queueAdd.try_pop(wBody);
            if (!wBody.expired()) {

                dynamicsWorld->addRigidBody(wBody.lock().get()->body);
                bodies.push_back(wBody);
            }
            else Debug::Log("lost rigidbody");

        }
        while (!queueDeleter.empty()) {
            std::weak_ptr<RigidBody> wBody;
            queueDeleter.try_pop(wBody);
            if (!wBody.expired()) {

                dynamicsWorld->removeRigidBody(wBody.lock().get()->body);
            }
            else Debug::Log("lost rigidbody");
        }
        dynamicsWorld->stepSimulation(Time::GetDeltaTime() * 1/1);
        for (auto lock_body = bodies.begin(); lock_body != bodies.end();++lock_body) {
            if (lock_body->expired()) {
                lock_body = bodies.erase(lock_body);
                --lock_body;
            }
            else {
                auto body = lock_body->lock();
                btTransform trans;

                body->body->getMotionState()->getWorldTransform(trans);
                auto quat = trans.getRotation();
                Vector4 quaat;
                quaat.x = quat.x();
                quaat.y = quat.y();
                quaat.z = quat.z();
                quaat.w = quat.w();
                
                auto vec = trans.getOrigin();
                auto pos = glm::vec3(
                    vec.x(), vec.y(), vec.z()
                );
                body->transform->UpdatePosition(pos, quaat);
            }

        }
    }
    void Physics::addRigidBody(std::weak_ptr<RigidBody> body)
    {
        queueAdd.push(body);

    }
    void Physics::removeRigidBody(std::weak_ptr<RigidBody> body)
    {
        queueDeleter.push(body);
    }
    Physics::Physics()
    {
        collisionConfiguration = std::unique_ptr<btDefaultCollisionConfiguration>(new btDefaultCollisionConfiguration());
        dispatcher = std::unique_ptr<btCollisionDispatcher>(new btCollisionDispatcher(collisionConfiguration.get()));
        overlappingPairCache = std::unique_ptr<btDbvtBroadphase>(new btDbvtBroadphase());
        solver = std::unique_ptr<btSequentialImpulseConstraintSolver>(new btSequentialImpulseConstraintSolver());
        dynamicsWorld = std::unique_ptr<btDiscreteDynamicsWorld>(
            new btDiscreteDynamicsWorld(dispatcher.get(), overlappingPairCache.get(), solver.get(), collisionConfiguration.get()));

        colliderFactory = std::unique_ptr<ColliderFactory>(new ColliderFactory(this));
        rigidBodyFactory = std::unique_ptr<RigidBodyFactory>(new RigidBodyFactory(this));
    }
    Physics::~Physics()
    {
    }
}