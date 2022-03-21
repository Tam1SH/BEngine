#pragma once
#include "stdafx.h"
#include "platform.hpp"
#include "ExecuteQueues.hpp"
#include <queue>
#include "Vector3.hpp"
#include "RenderWorld.hpp"
using BE_STD::shared_ptr;
using BE_STD::unique_ptr;
using BE_STD::optional;
using BE_STD::string;
using BE_STD::function;
using BE_STD::vector;
using BE_STD::list;

BE_NAMESPACE_STD_BEGIN

    template<class _Ty, class _Dx>
    class unique_ptr;
    template<class T>
    class shared_ptr;
    template<class T, class Alloc>
    class vector;
    template<class T, class Alloc>
    class list;

BE_NAMESPACE_STD_END

namespace BEbraEngine {
    class AbstractRender;
    class VulkanRender;
    class WorkSpace;
    class Physics;
    class GameObjectFactory;
    class ScriptManager;
    class Render;
    class SimpleCamera;
    class GameObject;
    class DirectionLight;
    class Time;
    class RigidBody;
    class Light;
    class ObjectFactoryFacade;
    class GameComponentCreateInfo;
}

namespace BEbraEngine {
    
    class ScriptState {
    public:

        ScriptState(AbstractRender& render, Physics& physics);

        void scriptInit();

        void clearObjects();

        void fixedUpdate();

        void update();

        void updateState();

        void addObject(shared_ptr<GameObject> object, const GameComponentCreateInfo& info);

        void removeObject(shared_ptr<GameObject> object, function<void(GameObject&)> callback);

        void addCamera(SimpleCamera& camera);

        void addLight(Light& light);

        void addDirLight(DirectionLight& light);

        shared_ptr<GameObject> getShared(const GameObject& object);

        ~ScriptState();

        

    private:

        vector<shared_ptr<GameObject>> objects_;

        vector<shared_ptr<Light>> lights;

        tbb::concurrent_hash_map<const GameObject*, shared_ptr<GameObject>> objectsCache;

        ExecuteQueues<function<void()>> queues;

        AbstractRender* render;

        Physics* physics;
        
        unique_ptr<RenderWorld> renderWorld;

        unique_ptr<ObjectFactoryFacade> scriptObjectFactory;

        unique_ptr<ScriptManager> scriptManager;



        shared_ptr<SimpleCamera> camera;

        shared_ptr<DirectionLight> globalLight;

        shared_ptr<Light> light;

        shared_ptr<GameObject> sphere;

        shared_ptr<GameObject> player;

        list<shared_ptr<GameObject>> bounds;
        list<shared_ptr<GameObject>> objects;
        Vector3 scale;
        Vector3 rotate;
        Vector3 lightColor;
        int step;
        bool addred = true;
        bool addblue;
        bool addgreen;

        bool lookatobject;
        Vector3* posofobject;

        Vector3* pos;
        Vector3* direction;
        RigidBody* body;
    };
}
