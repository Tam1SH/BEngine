#pragma once
#include "stdafx.h"
#include "RenderObjectCreator.hpp"
#include "Listener.hpp"

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

    //TODO: ListenerOnTick
    class GameLogic : public IListenerOnRender {
    public:

        GameLogic(std::shared_ptr<AbstractRender> render, std::shared_ptr<WorkSpace> workspace, Camera* camera);

        void ScriptInit();

        void onUpdateFrame() override;

        void Update();

        ~GameLogic();

    private:
        std::shared_ptr<AbstractRender> render;
        std::shared_ptr<Physics> physics;
        std::shared_ptr<WorkSpace> workspace;
        std::shared_ptr<ScriptManager> scriptManager;

        std::unique_ptr<GameObjectFactory> objectFactory;
        Camera* camera;
    };
}
