#include "platform.hpp"
#include <Physics/LinearMath/btIDebugDraw.h>

//#include "BulletCollision/BroadphaseCollision/btBroadphaseInterface.h"
#include "BulletCollision/CollisionDispatch/btCollisionDispatcherMt.h"
#include "BulletDynamics/Dynamics/btSimulationIslandManagerMt.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorldMt.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolverMt.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "BulletDynamics/ConstraintSolver/btNNCGConstraintSolver.h"
#include <Physics/btBulletDynamicsCommon.h>
#include <tbb.h>


import <vector>;
import <memory>;
import <functional>;
import <optional>;
import ExecuteQueues;

import Vector4;
import Vector3;
import RigidBody;
import Collider;
import Transform;
import Quaternion;
import Render;

class btDynamicsWorld;
class btConstraintSolverPoolMt;
class btSequentialImpulseConstraintSolverMt;
class btVector3;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btConstraintSolver;
using std::unique_ptr;
using std::optional;
using std::string;
using std::function;

BE_NAMESPACE_STD_BEGIN

    template<class T, class D>
    class unique_ptr;

BE_NAMESPACE_STD_END


namespace BEbraEngine {
    class Render;
    class RigidBody;
    class RigidBodyFactory;
    class ColliderFactory;
    class ParallelDiscreteDynamicsWorld;
    class btTaskSchedulerManager;
}

namespace BEbraEngine {
    
    ATTRIBUTE_ALIGNED16(class)
    ParallelDiscreteDynamicsWorld : public btDiscreteDynamicsWorldMt
    {

    public:
        BT_DECLARE_ALIGNED_ALLOCATOR();


        ParallelDiscreteDynamicsWorld(btDispatcher* dispatcher,
            btBroadphaseInterface* pairCache,
            btConstraintSolverPoolMt* constraintSolver,
            btSequentialImpulseConstraintSolverMt* constraintSolverMt,
            btCollisionConfiguration* collisionConfiguration) : btDiscreteDynamicsWorldMt(dispatcher, pairCache, constraintSolver, constraintSolverMt, collisionConfiguration)
        {
            btSimulationIslandManagerMt* islandMgr = static_cast<btSimulationIslandManagerMt*>(m_islandManager);
            islandMgr->setIslandDispatchFunction(btSimulationIslandManagerMt::parallelIslandDispatch);
        }

    };

    class DebugDrawer : public btIDebugDraw {
    public:

        void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

        DebugDrawer(Render& render);

        void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}

        void reportErrorWarning(const char* warningString) { }

        void draw3dText(const btVector3& location, const char* textString) { }

        void setDebugMode(int debugMode) { }

        int getDebugMode() const { return btIDebugDraw::DBG_DrawWireframe; }
    private:
        Render* render;
        uint32_t linesToDraw;
    };

    
    class Physics {
    public:

        optional<Collider*> getObjectRayCast(const Vector3& start, Vector3& end);

        void update();

        void setDebugDrawer(btIDebugDraw* drawer);

        ColliderFactory* getColliderFactory() { return colliderFactory.get(); }

        RigidBodyFactory* getRigidBodyFactory() { return rigidBodyFactory.get(); }

        void addRigidBody(RigidBody& body);

        void removeRigidBody(RigidBody& body);

        void removeCollider(Collider& col);

        void debugDraw();

        void setCollder(RigidBody& body, Collider& collider);

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

        std::vector<RigidBody*> bodies;

        unique_ptr<btIDebugDraw> drawer;

        unique_ptr<ColliderFactory> colliderFactory;

        unique_ptr<RigidBodyFactory> rigidBodyFactory;

        ExecuteQueues<function<void()>> queues;


    };
}

