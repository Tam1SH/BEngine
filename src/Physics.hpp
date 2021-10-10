#pragma once
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#include <memory>
#include <list>

namespace BEbraEngine {

    class RigidBody;
    class Physics {
    private:
        friend class GameObjectFactory;


        btDefaultCollisionConfiguration* collisionConfiguration;

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        btCollisionDispatcher* dispatcher;

        ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
        btBroadphaseInterface* overlappingPairCache;

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        btSequentialImpulseConstraintSolver* solver;

        btDiscreteDynamicsWorld* dynamicsWorld;

    private:
        std::list<std::weak_ptr<RigidBody>> bodies;
    public:
        void Update();
        //TODO: нормально?
        btDiscreteDynamicsWorld* GetDynamicsWorld();

        void AddObject(std::weak_ptr<RigidBody> body);

        Physics();

        ~Physics();
    };
}

