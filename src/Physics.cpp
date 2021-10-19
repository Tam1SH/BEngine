#include "Physics.hpp"
#include "RigidBoby.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Time.hpp"
//TODO: сделать так, чтобы физика параллельно обрабатывалась бл€ть(жаль производительность растЄт ниху€ не линейно). ѕерекомпилить с использованием TBB(пока только дл€ винды)
namespace BEbraEngine {


    void Physics::Update()
    {
        dynamicsWorld->stepSimulation(Time::GetDeltaTime() * 1/5);
        for (auto lock_body = bodies.begin(); lock_body != bodies.end();++lock_body) {
            if (lock_body->expired()) {
                lock_body = bodies.erase(lock_body);
                --lock_body;
            }
            else {
                auto body = lock_body->lock();
                btTransform trans;

                body->body->getMotionState()->getWorldTransform(trans);

                auto vec = trans.getOrigin();
                auto pos = glm::vec3(
                    vec.x(), vec.y(), vec.z()
                );

                body->transform->UpdatePosition(pos);
            }

        }
    }
    btDiscreteDynamicsWorld* Physics::GetDynamicsWorld()
    {
        return dynamicsWorld;
    }
    void Physics::AddObject(std::weak_ptr<RigidBody> body)
    {
        bodies.push_back(body);
    }
    Physics::Physics()
    {
        RigidBody::SetPhysics(this);
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
        overlappingPairCache = new btDbvtBroadphase();
        solver = new btSequentialImpulseConstraintSolver();
        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    }
    Physics::~Physics()
    {

        delete collisionConfiguration;
        delete dispatcher;
        delete solver;
        delete overlappingPairCache;
        delete dynamicsWorld;

    }
}