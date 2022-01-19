#pragma once
#include "stdafx.h"

#include <Physics/btBulletCollisionCommon.h>
#include <Physics/btBulletDynamicsCommon.h>

#include "ColliderFactory.hpp"
#include "RigidBodyFactory.hpp"
#include "ExecuteQueues.hpp"

class btConstraintSolverPoolMt;
class btSequentialImpulseConstraintSolverMt;

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

    class Physics {
    public:

        void update();

        ColliderFactory* getColliderFactory() { return colliderFactory.get(); }

        RigidBodyFactory* getRigidBodyFactory() { return rigidBodyFactory.get(); }

        void addRigidBody(RigidBody& body);

        void removeRigidBody(RigidBody& body);

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

        std::list<RigidBody*> bodies;

        std::vector<RigidBody*> _bodies;

        std::unique_ptr<ColliderFactory> colliderFactory;

        std::unique_ptr<RigidBodyFactory> rigidBodyFactory;

        ExecuteQueues<std::function<void()>> queues;


    };
}

