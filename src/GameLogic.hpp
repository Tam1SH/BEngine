#pragma once
#include "stdafx.h"
#include "VulkanRenderObjectFactory.hpp"
#include <queue>
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
    class IProxyGameObjectFactory;
    class GameObject;
}
namespace std {
    template<class _Ty, class _Dx>
    class unique_ptr;
    template<class T>
    class shared_ptr;
}
namespace BEbraEngine {
    //TODO: полигон блять для испытаний(делай скрипты)
    
    class GameLogic {
    public:

        GameLogic(std::shared_ptr<AbstractRender> render, std::shared_ptr<WorkSpace> workspace, std::shared_ptr<Physics> physics);

        void scriptInit();

        void clearObjects();

        void fixedUpdate();

        void update();

        ~GameLogic();

    private:
        std::shared_ptr<AbstractRender> render;
       
        std::shared_ptr<WorkSpace> workspace;

        std::unique_ptr<GameObjectFactory> objectFactory;

        std::unique_ptr<IProxyGameObjectFactory> scriptObjectFactory;

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
