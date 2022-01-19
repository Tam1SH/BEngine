#pragma once
#include "stdafx.h"
#include "ExecuteQueues.hpp"
#include <queue>
#include "Vector3.hpp"
using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

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
    class PointLight;
    class ObjectFactoryFacade;
    class GameComponentCreateInfo;
}
namespace std {
    template<class _Ty, class _Dx>
    class unique_ptr;
    template<class T>
    class shared_ptr;

}
namespace BEbraEngine {
    //TODO: полигон блять для испытаний(делай скрипты)
    
    class ScriptState {
    public:

        ScriptState(AbstractRender& render, Physics& physics);

        void scriptInit();

        void clearObjects();

        void fixedUpdate();

        void update();

        void updateState();

        void addObject(GameObject& object, const GameComponentCreateInfo& info);

        void removeObject(GameObject& object, std::function<void(GameObject&)> callback);

        void addCamera(SimpleCamera& camera);

        void addLight(PointLight& light);

        void addDirLight(DirectionLight& light);

        ~ScriptState();

    private:

        std::vector<shared_ptr<GameObject>> objects_;

        ExecuteQueues<std::function<void()>> queues;

        AbstractRender* render;

        Physics* physics;

        std::unique_ptr<ObjectFactoryFacade> scriptObjectFactory;

        std::unique_ptr<ScriptManager> scriptManager;

        std::shared_ptr<SimpleCamera> camera;

        std::shared_ptr<DirectionLight> globalLight;

        std::shared_ptr<PointLight> light;
        std::list<std::shared_ptr<GameObject>> bounds;
        std::list<std::shared_ptr<GameObject>> objects;
        std::list<std::shared_ptr<PointLight>> lights;
        Vector3 scale;
        Vector3 rotate;
        Vector3 lightColor;
        int step;
        bool addred = true;
        bool addblue;
        bool addgreen;

        bool lookatobject;
        Vector3* posofobject;
    };
}
