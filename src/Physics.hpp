#pragma once
#include "stdafx.h"

#include <Physics/btBulletCollisionCommon.h>
#include <Physics/btBulletDynamicsCommon.h>

#include "ColliderFactory.hpp"
#include "RigidBodyFactory.hpp"

namespace BEbraEngine {
    class RigidBody;
}
namespace BEbraEngine {

    class Physics {
    public:

        void Update();

        ColliderFactory* getColliderFactory() { return colliderFactory.get(); }

        RigidBodyFactory* getRigidBodyFactory() { return rigidBodyFactory.get(); }

        void addRigidBody(std::shared_ptr<RigidBody> body);

        void removeRigidBody(std::shared_ptr<RigidBody> body);

        Physics();

        ~Physics();
    private:

        std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration;

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        std::unique_ptr<btCollisionDispatcher> dispatcher;
        ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
        std::unique_ptr<btBroadphaseInterface> overlappingPairCache;

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        std::unique_ptr<btSequentialImpulseConstraintSolver> solver;

        std::unique_ptr<btDiscreteDynamicsWorld> dynamicsWorld;

        std::list<std::shared_ptr<RigidBody>> bodies;

        tbb::concurrent_queue<std::shared_ptr<RigidBody>> queueAdd;

        tbb::concurrent_queue<std::shared_ptr<RigidBody>> queueDeleter;

        std::unique_ptr<ColliderFactory> colliderFactory;

        std::unique_ptr<RigidBodyFactory> rigidBodyFactory;

        std::mutex addremovesync;
    };
}

