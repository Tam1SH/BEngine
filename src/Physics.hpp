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
    private:
        
        std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration;

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        std::unique_ptr<btCollisionDispatcher> dispatcher;
        ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
        std::unique_ptr<btBroadphaseInterface> overlappingPairCache;

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        std::unique_ptr<btSequentialImpulseConstraintSolver> solver;

        std::unique_ptr<btDiscreteDynamicsWorld> dynamicsWorld;

        std::list<std::weak_ptr<RigidBody>> bodies;

        std::unique_ptr<ColliderFactory> colliderFactory;

        std::unique_ptr<RigidBodyFactory> rigidBodyFactory;
    public:

        void Update();
        ColliderFactory* getColliderFactory() { return colliderFactory.get(); }
        RigidBodyFactory* getRigidBodyFactory() { return rigidBodyFactory.get(); }
        void addRigidBody(btRigidBody* body);
        void removeRigidBody(btRigidBody* body);
        void addObject(std::weak_ptr<RigidBody> body);

        Physics();

        ~Physics();
    };
}

