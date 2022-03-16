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
    class AbstractRender;
    class RigidBody;
    class ParallelDiscreteDynamicsWorld;
    class btTaskSchedulerManager;
}

namespace BEbraEngine {

    class DebugDrawer : public btIDebugDraw {
    public:

        void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

        DebugDrawer(AbstractRender& render);

        void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override {}

        void reportErrorWarning(const char* warningString) override { }

        void draw3dText(const btVector3& location, const char* textString) override { }

        void setDebugMode(int debugMode) override { }

        int getDebugMode() const override { return btIDebugDraw::DBG_DrawWireframe; }
    private:
        AbstractRender* render;
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

        vector<RigidBody*> bodies;

        unique_ptr<btIDebugDraw> drawer;

        unique_ptr<ColliderFactory> colliderFactory;

        unique_ptr<RigidBodyFactory> rigidBodyFactory;

        ExecuteQueues<function<void()>> queues;


    };
}

