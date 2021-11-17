#pragma once
#include "stdafx.h"
#include "RenderObjectFactory.hpp"
#include "Listener.hpp"
#include "GameObject.hpp"
#include "RenderObject.hpp"
#include <queue>
#include "IProxyGameObjectFactory.hpp"
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
}
namespace BEbraEngine {
    //TODO: полигон блять для испытаний(делай скрипты)
    //TODO: Идиотская затея была делать IListener
    
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
        //Depresed)
        std::unique_ptr<GameObjectFactory> objectFactory;

        std::unique_ptr<IProxyGameObjectFactory> scriptObjectFactory;

        Camera* camera;

        std::shared_ptr<DirLight> globalLight;
        std::shared_ptr<GameObject> object;
        std::shared_ptr<PointLight> light;

        std::list<std::shared_ptr<GameObject>> objects;
        std::list<std::shared_ptr<PointLight>> lights;
        Vector3 scale;
        Vector3 rotate;
    };
}
