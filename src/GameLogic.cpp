#include "stdafx.h"
#include "GameLogic.hpp"
#include "ScriptManager.hpp"
#include "GameObjectFactory.hpp"
#include "Time.hpp"
#include "Camera.hpp"
#include "Physics.hpp"
#include "VulkanRender.hpp"
#include "Input.hpp"
#include "Vector3.hpp"
#include "RigidBoby.hpp"
//TODO: ���������� ������ ���� �����.
namespace BEbraEngine {

    std::shared_ptr<Light> light;
    std::shared_ptr<GameObject> object;
    std::queue<std::shared_ptr<GameObject>> objects;
    Vector3 scale;

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
        object = GameObject::New(Vector3(1,0,0));
        object->GetComponent<RigidBody>()->SetDynamic(false);
        light = objectFactory->createLight(Vector3(0));
    }

    void GameLogic::onUpdateFrame()
    {
        Update();
    }
    static void clearObjects() {
        if(!objects.empty())
            objects.pop();
    }
    void GameLogic::FixedUpdate() {
        if (Input::IsKeyPressed(KEY_CODE::KEY_R)) {
            auto obj = GameObject::New(camera->Position + (camera->Front * 5.f));
            obj->GetComponent<RigidBody>()->applyImpulse(camera->Front * 50.f, camera->Front);
            objects.push(obj);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_T)) {
            clearObjects();
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_E)) {
            light->transform->SetPosition(camera->Position);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_1)) {
            scale.x += 1;
            auto transform = object->GetComponent<Transform>();
            transform->SetScale(scale);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_2)) {
            scale.y += 1;
            auto transform = object->GetComponent<Transform>();
            transform->SetScale(scale);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_3)) {
            scale.z += 1;
            auto transform = object->GetComponent<Transform>();
            transform->SetScale(scale);

        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_4)) {
            scale.x -= 1;
            auto transform = object->GetComponent<Transform>();
            transform->SetScale(scale);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_5)) {
            scale.y -= 1;
            auto transform = object->GetComponent<Transform>();
            transform->SetScale(scale);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_6)) {
            scale.z -= 1;
            auto transform = object->GetComponent<Transform>();
            transform->SetScale(scale);

        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_7)) {
            scale = Vector3(1);
            auto transform = object->GetComponent<Transform>();
            transform->SetScale(scale);

        }

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
        static float time = 0;
        time += Time::GetDeltaTime();
        if (time > 1 / 60.f) {
            FixedUpdate();
            time = 0;
        }
        physics->Update();
        camera->Update();
        scriptManager->RunScripts();

    }

    GameLogic::~GameLogic()
    {
        //scriptManager.reset();
    }
}