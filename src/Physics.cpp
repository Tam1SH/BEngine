#include "stdafx.h"
#include "Physics.hpp"
#include "RigidBoby.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Quaternion.hpp"
#include "Time.hpp"
#include "Vector4.hpp"
#include "Collider.hpp"
#include "BulletCollision/CollisionDispatch/btCollisionDispatcherMt.h"
#include "BulletDynamics/Dynamics/btSimulationIslandManagerMt.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorldMt.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolverMt.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "BulletDynamics/ConstraintSolver/btNNCGConstraintSolver.h"
#include "AbstractRender.hpp"
#include <VulkanRender.hpp>
#include "Math.hpp"
namespace BEbraEngine {
    ATTRIBUTE_ALIGNED16(class)
    ParallelDiscreteDynamicsWorld : public btDiscreteDynamicsWorldMt
    {
        typedef btDiscreteDynamicsWorldMt ParentClass;

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

    void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
    {
        linesToDraw++;
        //render->drawLine(from, to, color);
    }
    DebugDrawer::DebugDrawer(AbstractRender& render)
    {
        this->render = &render;
    }

    class btTaskSchedulerManager
    {
        btAlignedObjectArray<btITaskScheduler*> m_taskSchedulers;
        btAlignedObjectArray<btITaskScheduler*> m_allocatedTaskSchedulers;

    public:
        btTaskSchedulerManager() {}
        void init()
        {

            addTaskScheduler(btGetSequentialTaskScheduler());
            if (btITaskScheduler* ts = btCreateDefaultTaskScheduler())
            {
                m_allocatedTaskSchedulers.push_back(ts);
                addTaskScheduler(ts);
            }
            addTaskScheduler(btGetOpenMPTaskScheduler());
            addTaskScheduler(btGetTBBTaskScheduler());
            addTaskScheduler(btGetPPLTaskScheduler());
            if (getNumTaskSchedulers() > 1)
            {
                // prefer a non-sequential scheduler if available
                btSetTaskScheduler(m_taskSchedulers[1]);
            }
            else
            {
                btSetTaskScheduler(m_taskSchedulers[0]);
            }
        }
        void shutdown()
        {
            for (int i = 0; i < m_allocatedTaskSchedulers.size(); ++i)
            {
                delete m_allocatedTaskSchedulers[i];
            }
            m_allocatedTaskSchedulers.clear();
        }

        void addTaskScheduler(btITaskScheduler* ts)
        {
            if (ts)
            {
                // if initial number of threads is 0 or 1,
                if (ts->getNumThreads() <= 1)
                {
                    // for OpenMP, TBB, PPL set num threads to number of logical cores
                    ts->setNumThreads(ts->getMaxNumThreads());
                }
                m_taskSchedulers.push_back(ts);
            }
        }
        int getNumTaskSchedulers() const { return m_taskSchedulers.size(); }
        btITaskScheduler* getTaskScheduler(int i) { return m_taskSchedulers[i]; }
    };


    enum SolverType
    {
        SOLVER_TYPE_SEQUENTIAL_IMPULSE,
        SOLVER_TYPE_SEQUENTIAL_IMPULSE_MT,

        SOLVER_TYPE_COUNT
    };

    btConstraintSolver* createSolverByType(SolverType t)
    {
        switch (t)
        {
        case SOLVER_TYPE_SEQUENTIAL_IMPULSE:
            return new btSequentialImpulseConstraintSolver();
        case SOLVER_TYPE_SEQUENTIAL_IMPULSE_MT:
            return new btSequentialImpulseConstraintSolverMt();
        default:
        {
        }
        }

        return NULL;
    }
    void Physics::update()
    {
        dynamicsWorld->stepSimulation(Time::deltaTime(), 1);
        dynamicsWorld->debugDrawWorld();
        //dynamicsWorld->setGravity(Vector3(0));
        for (auto body = bodies.begin(); body != bodies.end(); ++body) {

            btTransform trans;
            auto _body = (*body);
            _body->getRigidBody().getMotionState()->getWorldTransform(trans);
            auto quat = trans.getRotation();
            Vector4 quaat;
            quaat.x = quat.x();
            quaat.y = quat.y();
            quaat.z = quat.z();
            quaat.w = quat.w();
            
            auto vec = trans.getOrigin();

            auto pos = glm::vec3(
                vec.x(), vec.y(), vec.z()
            );
            auto& rigidbody = _body->getRigidBody();
            if (BEbraMath::length(rigidbody.getLinearVelocity()) > _body->getMaxVelocity()) {
                rigidbody.setLinearVelocity(BEbraMath::normalize(rigidbody.getLinearVelocity()) * _body->getMaxVelocity());
            }
            if (_body->getDynamic()) {
                _body->getTransform().updatePosition(pos);
                _body->getTransform().setQuat(Quaternion(quaat));
            }
            else {
                //_body->resetState();
            }

        }

        queues.execute();

    }

    void Physics::setDebugDrawer(btIDebugDraw* drawer)
    {
        this->drawer = std::unique_ptr<btIDebugDraw>(drawer);
        dynamicsWorld->setDebugDrawer(drawer);
    }

    void Physics::addRigidBody(RigidBody& body)
    {
        dynamicsWorld->addRigidBody(&body.getRigidBody());
        bodies.push_back(&body);
    }
    void Physics::removeRigidBody(RigidBody& body)
    {
        rigidBodyFactory->destroy(body);
        dynamicsWorld->removeRigidBody(&body.getRigidBody());
        bodies.remove(&body);
    }
    void Physics::removeCollider(Collider* col)
    {
        dynamicsWorld->removeCollisionObject(&col->get());
    }
    void Physics::debugDraw()
    {
        dynamicsWorld->debugDrawWorld();
    }
    void Physics::setCollder(RigidBody* body, Collider* collider)
    {
        colliderFactory->destroyCollider(rigidBodyFactory->getCollider(*body));

        rigidBodyFactory->setCollder(*body, collider);
    }
    Physics::Physics()
    {

        colliderFactory = std::unique_ptr<ColliderFactory>(new ColliderFactory(this));
        rigidBodyFactory = std::unique_ptr<RigidBodyFactory>(new RigidBodyFactory(this));
        if (false) {

            mgr = std::unique_ptr<btTaskSchedulerManager>(new btTaskSchedulerManager());
            mgr->init();

            btDefaultCollisionConstructionInfo cci;
            cci.m_defaultMaxPersistentManifoldPoolSize = 80000;
            cci.m_defaultMaxCollisionAlgorithmPoolSize = 80000;
            collisionConfiguration = std::unique_ptr<btDefaultCollisionConfiguration>(new btDefaultCollisionConfiguration(cci));

            overlappingPairCache = std::unique_ptr<btDbvtBroadphase>(new btDbvtBroadphase());


            {
                SolverType poolSolverType = SOLVER_TYPE_SEQUENTIAL_IMPULSE;
                btConstraintSolver* solvers[BT_MAX_THREAD_COUNT];
                int maxThreadCount = BT_MAX_THREAD_COUNT;
                for (int i = 0; i < maxThreadCount; ++i)
                {
                    solvers[i] = createSolverByType(poolSolverType);
                }
                solverPool = std::unique_ptr<btConstraintSolverPoolMt>(new btConstraintSolverPoolMt(solvers, maxThreadCount));
            }
            solver = std::unique_ptr<btSequentialImpulseConstraintSolverMt>(new btSequentialImpulseConstraintSolverMt());

            btAssert(btGetTaskScheduler() != NULL);

            dispatcher = std::unique_ptr<btCollisionDispatcherMt>(new btCollisionDispatcherMt(collisionConfiguration.get(), 40));
            dynamicsWorld = std::unique_ptr<ParallelDiscreteDynamicsWorld>(
                new ParallelDiscreteDynamicsWorld(dispatcher.get(),
                    overlappingPairCache.get(),
                    solverPool.get(),
                    static_cast<btSequentialImpulseConstraintSolverMt*>(solver.get()),
                    collisionConfiguration.get()));
        }
        else {

            collisionConfiguration = std::unique_ptr<btDefaultCollisionConfiguration>(new btDefaultCollisionConfiguration());

            overlappingPairCache = std::unique_ptr<btDbvtBroadphase>(new btDbvtBroadphase());

            dispatcher = std::unique_ptr<btCollisionDispatcher>(new btCollisionDispatcher(collisionConfiguration.get()));

            dynamicsWorld = std::unique_ptr<btDiscreteDynamicsWorld>(new btDiscreteDynamicsWorld(dispatcher.get(),
                overlappingPairCache.get(),
                solver.get(),
                collisionConfiguration.get()));
        }
        queues.setStrategy(ExecuteType::Single);

    }
    Physics::~Physics()
    {
        for (auto& body : bodies) {
            rigidBodyFactory->destroy(*body);
        }
        dynamicsWorld.reset();
    }
}