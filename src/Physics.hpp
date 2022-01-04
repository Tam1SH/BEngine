#pragma once
#include "stdafx.h"

#include <Physics/btBulletCollisionCommon.h>
#include <Physics/btBulletDynamicsCommon.h>

#include "ColliderFactory.hpp"
#include "RigidBodyFactory.hpp"
#include "ExecuteQueues.hpp"

class btConstraintSolverPoolMt;
class btSequentialImpulseConstraintSolverMt;

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace std {
    template<class T, class D>
    class unique_ptr;
}


namespace BEbraEngine {
    class RigidBody;
    class ParallelDiscreteDynamicsWorld;
    class btTaskSchedulerManager;
}

namespace BEbraEngine {

    struct PhysicsData {
        std::vector<std::shared_ptr<RigidBody>> bodies;
        std::vector<std::shared_ptr<Collider>> colliders;
    };

    class Physics {
    public:

        void update();

        void updateData(const PhysicsData& data);

        ColliderFactory* getColliderFactory() { return colliderFactory.get(); }

        RigidBodyFactory* getRigidBodyFactory() { return rigidBodyFactory.get(); }

        void addRigidBody(shared_ptr<RigidBody> body);

        void removeRigidBody(shared_ptr<RigidBody> body);

        void removeCollider(Collider* col);

        void setCollder(RigidBody* body, Collider* collider);

        Physics();

        ~Physics();
    private:

        std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration;

        std::unique_ptr<btCollisionDispatcher> dispatcher;

        std::unique_ptr<btBroadphaseInterface> overlappingPairCache;

        std::unique_ptr<btConstraintSolver> solver;

        std::unique_ptr<btDynamicsWorld> dynamicsWorld;

        std::unique_ptr<btConstraintSolverPoolMt> solverPool;

        std::unique_ptr<btTaskSchedulerManager> mgr;

        std::list<shared_ptr<RigidBody>> bodies;

        std::vector<std::shared_ptr<RigidBody>> _bodies;

        tbb::concurrent_queue<std::shared_ptr<RigidBody>> queueAdd;

        tbb::concurrent_queue<std::shared_ptr<RigidBody>> queueDeleter;

        std::unique_ptr<ColliderFactory> colliderFactory;

        std::unique_ptr<RigidBodyFactory> rigidBodyFactory;

        ExecuteQueues<std::function<void()>> queues;
        std::mutex addremovesync;


    };
}

