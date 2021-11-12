#include "stdafx.h"
#include "GameLogic.hpp"
#include "ScriptManager.hpp"
#include "Collider.hpp"
#include "GameObjectFactory.hpp"
#include "Time.hpp"
#include "Camera.hpp"
#include "Physics.hpp"
#include "VulkanRender.hpp"
#include "Input.hpp"
#include "Vector3.hpp"
#include "RigidBoby.hpp"
namespace BEbraEngine {


    GameLogic::GameLogic(std::shared_ptr<AbstractRender> render, std::shared_ptr<WorkSpace> workspace, Camera* camera, std::shared_ptr<Physics> physics)
    {
        this->workspace = workspace;
        this->physics = physics;
        this->render = std::shared_ptr<AbstractRender>(render);
        objectFactory = std::unique_ptr<GameObjectFactory>(new GameObjectFactory(this->render, physics));
        objectFactory->SetWorkSpace(workspace);
        //scriptManager->SetWorkSpace(workspace);
        this->camera = camera;


        ScriptInit();
    }

    void GameLogic::ScriptInit()
    {
        object = objectFactory->create(Vector3(0, 0, 0));
        object->GetComponent<RigidBody>()->SetDynamic(false);
        object->GetComponent<Collider>()->setScale(Vector3(100, 1, 100));
        object->GetComponent<Transform>()->SetScale(Vector3(100, 1, 100));
        globalLight = objectFactory->createDirLight(Vector3(0,-0.5f,0));
        auto light = objectFactory->createLight(camera->Position);
        lights.push(light);
        rotate = Vector3(0, -0.5f, 0);
    }

    void GameLogic::onUpdateFrame()
    {
        Update();
    }
    void GameLogic::clearObjects() {
        if (!objects.empty()) {

            //objects.pop();
            std::shared_ptr<GameObject> obj;
            obj = objects.front();
            objectFactory->Destroy(obj);
            objects.pop();
            //std::cout << "TotalCount" << static_cast<VulkanRenderObjectFactory*>(objectFactory->renderFactory)->_poolofObjects->getCount() << std::endl;

        }

    }
    void GameLogic::FixedUpdate() {

        if (Input::IsKeyPressed(KEY_CODE::KEY_R)) {
            auto obj = objectFactory->create(camera->Position + (camera->Front * 5.f));
            obj->GetComponent<RigidBody>()->applyImpulse(camera->Front * 50.f, camera->Front);
            Vector3 random_color = Vector3(
                (rand() % 255) / 255.f, (rand() % 255) / 255.f, (rand() % 255) / 255.f
            );
            auto renderobj = obj->GetComponent<RenderObject>();
            renderobj->setColor(random_color);
            objects.push(obj);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_T)) {
            clearObjects();
                    }
        if (Input::IsKeyPressed(KEY_CODE::KEY_C)) {
            if (!lights.empty())
            {
                std::shared_ptr<PointLight> light1;
                light1 = lights.front();
                lights.pop();
            }

        }
        if (Input::isKeyReleased(KEY_CODE::KEY_Q)) {
            std::cout << "PIZDA" << std::endl;
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_E)) {
            auto light = objectFactory->createLight(camera->Position);
            Vector3 random_color = Vector3(
                (rand() % 255) / 255.f, (rand() % 255) / 255.f, (rand() % 255) / 255.f
            );
            light->setColor(random_color);
            lights.push(light);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_1)) {

            rotate.y = 0.5f;
            globalLight->setDirection(rotate);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_2)) {
            rotate.y = -0.5f;
            globalLight->setDirection(rotate);
        }

    }
    void GameLogic::Update()
    {
        float speed = 1;
        if (Input::IsKeyPressed(KEY_CODE::KEY_LEFT_SHIFT)) {
            speed = 20;
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_A)) {
            camera->ProcessKeyboard(LEFT, Time::GetDeltaTime() * speed);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_D)) {
            camera->ProcessKeyboard(RIGHT, Time::GetDeltaTime() * speed);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_S)) {
            camera->ProcessKeyboard(BACKWARD, Time::GetDeltaTime()* speed);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_W)) {
            camera->ProcessKeyboard(FORWARD, Time::GetDeltaTime()* speed);
        }
        static float time = 0;
        time += Time::GetDeltaTime();
        if (time > 1 / 60.f) {
            FixedUpdate();
            time = 0;
        }
        physics->Update();
        camera->Update();
        //scriptManager->RunScripts();

    }

    GameLogic::~GameLogic()
    {
        //scriptManager.reset();
    }
}