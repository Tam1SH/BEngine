#pragma once
#include "platform.hpp"

#include "stdafx.h"



#include <Physics/btBulletCollisionCommon.h>
#include <Physics/btBulletDynamicsCommon.h>

#include "ColliderFactory.hpp"
#include "RigidBodyFactory.hpp"
#include "ExecuteQueues.hpp"

class btConstraintSolverPoolMt;
class btSequentialImpulseConstraintSolverMt;

using BE_STD::unique_ptr;
using BE_STD::optional;
using BE_STD::string;
using BE_STD::function;

BE_NAMESPACE_STD_BEGIN

    template<class T, class D>
    class unique_ptr;

BE_NAMESPACE_STD_END


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

        unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration;

        unique_ptr<btCollisionDispatcher> dispatcher;

        unique_ptr<btBroadphaseInterface> overlappingPairCache;

        unique_ptr<btConstraintSolver> solver;

        unique_ptr<btDynamicsWorld> dynamicsWorld;

        unique_ptr<btConstraintSolverPoolMt> solverPool;

        unique_ptr<btTaskSchedulerManager> mgr;

        list<RigidBody*> bodies;

        vector<RigidBody*> _bodies;

        unique_ptr<ColliderFactory> colliderFactory;

        unique_ptr<RigidBodyFactory> rigidBodyFactory;

        ExecuteQueues<function<void()>> queues;


    };
}

