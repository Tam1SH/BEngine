#pragma once
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#include <memory>
#include <list>
namespace BEbraEngine {
    class RigidBody;
}
namespace BEbraEngine {

    class Physics {
    private:
        friend class GameObjectFactory;


        std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration;

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        std::unique_ptr<btCollisionDispatcher> dispatcher;

        ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
        std::unique_ptr<btBroadphaseInterface> overlappingPairCache;

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        std::unique_ptr<btSequentialImpulseConstraintSolver> solver;

        std::unique_ptr<btDiscreteDynamicsWorld> dynamicsWorld;

    private:
        std::list<std::weak_ptr<RigidBody>> bodies;
    public:
        void Update();

        void addRigidBody(btRigidBody* body);
        void removeRigidBody(btRigidBody* body);
        void AddObject(std::weak_ptr<RigidBody> body);

        Physics();

        ~Physics();
    };
}

