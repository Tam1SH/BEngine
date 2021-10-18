#include "GameLogic.h"
#include "ScriptManager.h"
#include "GameObjectFactory.hpp"
#include "Time.hpp"
#include "Camera.hpp"
#include "Physics.hpp"
#include "VulkanRender.h"
#include "Input.hpp"
//TODO: занимается вообще всем нахуй.
namespace BEbraEngine {


    GameLogic::GameLogic(VulkanRender* render, std::shared_ptr<WorkSpace> workspace)
    {
        scriptManager = std::shared_ptr<ScriptManager>(new ScriptManager());
        this->workspace = workspace;
        this->render = std::shared_ptr<Render>(new Render(render));
        physics = std::shared_ptr<Physics>(new Physics());
        objectFactory = std::unique_ptr<GameObjectFactory>(new GameObjectFactory(this->render, physics));
        objectFactory->SetWorkSpace(workspace);
        scriptManager->SetWorkSpace(workspace);
        camera = std::shared_ptr<Camera>(new Camera(0, 0, glm::vec3(0,1,10)));
        camera->SetRender(render);
        creator.render = render;
        creator.CreateStorageBuffer(sizeof(glm::mat4) * 2, camera->buffer);
        camera->CreateCameraSet();
        render->camera = camera.get();


        ScriptInit();
    }

    void GameLogic::ScriptInit()
    {
        //scriptManager->LoadScripts();

        auto obj = GameObject::New();
        //auto script = scriptManager->GetScriptByName(L"hello_world.js");
        //script->SetActive(true);
        //obj->AddComponent(script);
        //scriptManager->InitScripts();
    }

    void GameLogic::onUpdateFrame()
    {
        Update();
    }

    void GameLogic::Update()
    {
        Time::UpdateTime();
        
        if (Input::IsKeyPressed(KEY_CODE::KEY_A)) {
            camera->ProcessKeyboard(LEFT, Time::GetDeltaTime());
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_D)) {
            camera->ProcessKeyboard(RIGHT, Time::GetDeltaTime());
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_S)) {
            camera->ProcessKeyboard(BACKWARD, Time::GetDeltaTime());
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_W)) {
            camera->ProcessKeyboard(FORWARD, Time::GetDeltaTime());
        }

        camera->Update();
        scriptManager->RunScripts();
        physics->Update();
    }

    GameLogic::~GameLogic()
    {
        scriptManager.reset();
        workspace->RemoveAll();
    }
}