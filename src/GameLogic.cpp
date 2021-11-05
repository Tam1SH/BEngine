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

    std::shared_ptr<Light> light;
    GameLogic::GameLogic(std::shared_ptr<AbstractRender> render, std::shared_ptr<WorkSpace> workspace, Camera* camera, std::shared_ptr<Physics> physics)
    {
        scriptManager = std::shared_ptr<ScriptManager>(new ScriptManager());
        this->workspace = workspace;
        this->physics = physics;
        this->render = std::shared_ptr<AbstractRender>(render);
        objectFactory = std::unique_ptr<GameObjectFactory>(new GameObjectFactory(this->render, physics));
        objectFactory->SetWorkSpace(workspace);
        scriptManager->SetWorkSpace(workspace);
        this->camera = camera;


        ScriptInit();
    }

    void GameLogic::ScriptInit()
    {
        auto obj = GameObject::New(Vector3(1,0,0));
        light = objectFactory->createLight(Vector3(0));
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
        if (Input::IsKeyPressed(KEY_CODE::KEY_E)) {
            light->transform->SetPosition(camera->Position);
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