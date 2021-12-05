#pragma once
#include "stdafx.h"

#include <Physics/btBulletCollisionCommon.h>
#include <Physics/btBulletDynamicsCommon.h>

#include "ColliderFactory.hpp"
#include "RigidBodyFactory.hpp"
#include "ExecuteQueues.hpp"

class btConstraintSolverPoolMt;
class btSequentialImpulseConstraintSolverMt;

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

    class PhysicsData {
        std::vector<std::shared_ptr<RigidBody>> bodies;
        std::vector<std::shared_ptr<Collider>> colliders;
    };

    class Physics {
    public:

        void update();

        ColliderFactory* getColliderFactory() { return colliderFactory.get(); }

        RigidBodyFactory* getRigidBodyFactory() { return rigidBodyFactory.get(); }

        void addRigidBody(std::shared_ptr<RigidBody> body);

        void removeRigidBody(std::shared_ptr<RigidBody> body);

        void removeCollider(std::shared_ptr<Collider> col);

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

        std::list<std::shared_ptr<RigidBody>> bodies;

        std::vector<std::shared_ptr<RigidBody>> _bodies;

        tbb::concurrent_queue<std::shared_ptr<RigidBody>> queueAdd;

        tbb::concurrent_queue<std::shared_ptr<RigidBody>> queueDeleter;

        std::unique_ptr<ColliderFactory> colliderFactory;

        std::unique_ptr<RigidBodyFactory> rigidBodyFactory;

        ExecuteQueues<std::function<void()>> queues;
        std::mutex addremovesync;


    };
}

