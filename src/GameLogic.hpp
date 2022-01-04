#pragma once
#include "stdafx.h"
#include "IProxyGameObjectFactory.hpp"
#include "VulkanRenderObjectFactory.hpp"
#include "ExecuteQueues.hpp"
#include <queue>

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace BEbraEngine {
    class VulkanRender;
    class WorkSpace;
    class Physics;
    class GameObjectFactory;
    class ScriptManager;
    class Render;
    class Camera;
    class Time;
    class ScriptObjectFactory;
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

        ScriptState(std::shared_ptr<AbstractRender> render, std::shared_ptr<WorkSpace> workspace, std::shared_ptr<Physics> physics);

        void scriptInit();

        void clearObjects();

        void fixedUpdate();

        void update();

        void updateState();

        void addObject(shared_ptr<GameObject> object, const GameObject::GameObjectCreateInfo& info = {});

        void removeObject(shared_ptr<GameObject> object);

        void addCamera(shared_ptr<Camera> camera);

        void addLight(shared_ptr<PointLight> light);

        void addDirLight(shared_ptr<DirectionLight> light);

        ~ScriptState();

    private:

        std::vector<shared_ptr<GameObject>> objects_;

        ExecuteQueues<std::function<void()>> queues;

        std::shared_ptr<AbstractRender> render;

        std::shared_ptr<Physics> physics;

        std::unique_ptr<ScriptObjectFactory> scriptObjectFactory;

        std::unique_ptr<ScriptManager> scriptManager;

        std::shared_ptr<Camera> camera;

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
