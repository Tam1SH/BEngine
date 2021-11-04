#include "stdafx.h"
#include "GameLogic.hpp"
#include "ScriptManager.hpp"
#include "GameObjectFactory.hpp"
#include "Time.hpp"
#include "Camera.hpp"
#include "Physics.hpp"
#include "VulkanRender.hpp"
#include "Input.hpp"
#include "Render.hpp"
#include "Vector3.hpp"
//TODO: ���������� ������ ���� �����.
namespace BEbraEngine {


    GameLogic::GameLogic(std::shared_ptr<AbstractRender> render, std::shared_ptr<WorkSpace> workspace, Camera* camera)
    {
        scriptManager = std::shared_ptr<ScriptManager>(new ScriptManager());
        this->workspace = workspace;
        this->render = std::shared_ptr<AbstractRender>(render);
        physics = std::shared_ptr<Physics>(new Physics());
        objectFactory = std::unique_ptr<GameObjectFactory>(new GameObjectFactory(this->render, physics));
        objectFactory->SetWorkSpace(workspace);
        scriptManager->SetWorkSpace(workspace);
        this->camera = camera;


        ScriptInit();
    }

    void GameLogic::ScriptInit()
    {
        //scriptManager->LoadScripts();
        GameObject::New(Vector3(0));
        auto obj = GameObject::New(Vector3(3));
        auto light = std::shared_ptr<Light>(objectFactory->createLight(Vector3(2)));
        light->transform = obj->GetComponent<Transform>();
        obj->AddComponent(light);
        render->addLight(light);
        //GameObject::New(Vector3(1));
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
        //scriptManager.reset();
    }
}