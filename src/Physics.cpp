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
#include "Math.hpp"
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

    void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
    {
        linesToDraw++;
        render->drawLine(from, to, color);
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
            this;
            std::cout << btGetTBBTaskScheduler() << std::endl;
            
            addTaskScheduler(btGetTBBTaskScheduler());
            btSetTaskScheduler(m_taskSchedulers[0]);

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
                btSetTaskScheduler(m_taskSchedulers[0]);
            }
            //else throw std::exception();
        }
        int getNumTaskSchedulers() const { return m_taskSchedulers.size(); }
        btITaskScheduler* getTaskScheduler(int i) { return m_taskSchedulers[i]; }
    };


    optional<Collider*> Physics::getObjectRayCast(const Vector3& start, Vector3& end)
    {
        btCollisionWorld::ClosestRayResultCallback result(start, end);
        dynamicsWorld->rayTest(start, Vector3(0), result);
        auto collider = static_cast<Collider*>(result.m_collisionObject->getUserPointer());
        return optional<Collider*>(collider);
    }

    void Physics::update()
    {

        dynamicsWorld->stepSimulation(Time::deltaTime(), 1);
        
        tbb::parallel_for<size_t>(0, bodies.size(), [&](int i) {

            auto& body = *bodies[i];
            btTransform trans;
            auto& rigidbody = body.getRigidBody();
            rigidbody.getMotionState()->getWorldTransform(trans);
            const auto quat = trans.getRotation();
            const auto& pos = trans.getOrigin();

            if (BEbraMath::length(rigidbody.getLinearVelocity()) > body.getMaxVelocity()) {

                auto velocity = BEbraMath::normalize(rigidbody.getLinearVelocity()) * body.getMaxVelocity();

                rigidbody.setLinearVelocity(velocity);
            }
            body.getTransform().setPosition(pos);
            body.getTransform().setRotation(quat);
        });

        //dynamicsWorld->debugDrawWorld(); 
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
        auto iter = std::remove(bodies.begin(), bodies.end(), &body);
        bodies.erase(iter);
    }

    void Physics::removeCollider(Collider& col)
    {
        dynamicsWorld->removeCollisionObject(&col.get());
    }

    void Physics::debugDraw()
    {
        dynamicsWorld->debugDrawWorld();
    }

    void Physics::setCollder(RigidBody& body, Collider& collider)
    {
        colliderFactory->destroyCollider(rigidBodyFactory->getCollider(body));

        rigidBodyFactory->setCollder(body, collider);
    }
    Physics::Physics()
    {

        colliderFactory = std::unique_ptr<ColliderFactory>(new ColliderFactory(*this));
        rigidBodyFactory = std::unique_ptr<RigidBodyFactory>(new RigidBodyFactory(*this));
        if (true) {

            mgr = std::unique_ptr<btTaskSchedulerManager>(new btTaskSchedulerManager());
            mgr->init();

            btDefaultCollisionConstructionInfo cci;
            cci.m_defaultMaxPersistentManifoldPoolSize = 80000;
            cci.m_defaultMaxCollisionAlgorithmPoolSize = 80000;
            collisionConfiguration = std::unique_ptr<btDefaultCollisionConfiguration>(new btDefaultCollisionConfiguration(cci));

            overlappingPairCache = std::unique_ptr<btDbvtBroadphase>(new btDbvtBroadphase());

            btConstraintSolver* solvers[BT_MAX_THREAD_COUNT];
            for (int i = 0; i < BT_MAX_THREAD_COUNT; ++i)
            {
                solvers[i] = new btSequentialImpulseConstraintSolverMt(); 
            }
            solverPool = std::unique_ptr<btConstraintSolverPoolMt>(new btConstraintSolverPoolMt(solvers, BT_MAX_THREAD_COUNT));
            
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
        dynamicsWorld.reset();
        bodies.clear();
    }
}