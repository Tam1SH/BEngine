#pragma once
#include "stdafx.h"
#include "RenderObjectCreator.hpp"
#include "Listener.hpp"
#include "GameObject.hpp"
#include "RenderObject.hpp"
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
}
namespace BEbraEngine {
    //TODO: полигон блять для испытаний(делай скрипты)
    //TODO: ListenerOnTick
    class GameLogic : public IListenerOnRender {
    public:

        GameLogic(std::shared_ptr<AbstractRender> render, std::shared_ptr<WorkSpace> workspace, Camera* camera, std::shared_ptr<Physics> physics);

        void ScriptInit();

        void onUpdateFrame() override;

        void clearObjects();

        void FixedUpdate();

        void Update();

        ~GameLogic();

    private:
        std::shared_ptr<AbstractRender> render;
        std::shared_ptr<Physics> physics;
        std::shared_ptr<WorkSpace> workspace;
        std::shared_ptr<ScriptManager> scriptManager;

        std::unique_ptr<GameObjectFactory> objectFactory;
        Camera* camera;

        std::shared_ptr<DirLight> globalLight;
        std::shared_ptr<GameObject> object;

        std::queue<std::shared_ptr<GameObject>> objects;
        std::queue<std::shared_ptr<PointLight>> lights;
        Vector3 scale;
        Vector3 rotate;
    };
}
