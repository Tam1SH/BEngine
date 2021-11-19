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
            std::shared_ptr<RigidBody> body;
            if (queueAdd.try_pop(body)) {
                dynamicsWorld->addRigidBody(body.get()->body);
                bodies.push_back(body);
            }

        }
        while (!queueDeleter.empty()) {
            std::shared_ptr<RigidBody> body;
            if (queueDeleter.try_pop(body)) {
                dynamicsWorld->removeRigidBody(body.get()->body);
                bodies.remove(body);
            }
        }
        dynamicsWorld->stepSimulation(Time::GetDeltaTime() * 1/1);
        for (auto body = bodies.begin(); body != bodies.end();++body) {

            //auto body = lock_body->lock();
            btTransform trans;
            auto _body = (*body);
            _body->body->getMotionState()->getWorldTransform(trans);
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
            if(_body->getDynamic())
                _body->transform->UpdatePosition(pos, quaat);

        }
    }
    void Physics::addRigidBody(std::shared_ptr<RigidBody> body)
    {
        queueAdd.push(body);

    }
    void Physics::removeRigidBody(std::shared_ptr<RigidBody> body)
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