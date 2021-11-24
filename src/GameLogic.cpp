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
#include "GameObject.hpp"
#include "RenderObject.hpp"
#include "Transform.hpp"
namespace BEbraEngine {


    GameLogic::GameLogic(std::shared_ptr<AbstractRender> render, std::shared_ptr<WorkSpace> workspace, Camera* camera, std::shared_ptr<Physics> physics)
    {
        this->workspace = workspace;
        this->render = std::shared_ptr<AbstractRender>(render);
        objectFactory = std::unique_ptr<GameObjectFactory>(new GameObjectFactory(this->render, physics));
        objectFactory->SetWorkSpace(workspace);
        //scriptManager->SetWorkSpace(workspace);
        this->camera = camera;


        ScriptInit();
    }

    void GameLogic::ScriptInit()
    {
        object = objectFactory->create(Vector3(0, 100, -100));
        object->getComponent<RigidBody>()->setDynamic(false);
        object->getComponent<Collider>()->setScale(Vector3(100, 100, 1));
        object->getComponent<Transform>()->SetScale(Vector3(100, 100, 1));

        object2 = objectFactory->create(Vector3(0, 100, 100));
        object2->getComponent<RigidBody>()->setDynamic(false);
        object2->getComponent<Collider>()->setScale(Vector3(100, 100, 1));
        object2->getComponent<Transform>()->SetScale(Vector3(100, 100, 1));

        object3 = objectFactory->create(Vector3(-100, 100, 0));
        object3->getComponent<RigidBody>()->setDynamic(false);
        object3->getComponent<Collider>()->setScale(Vector3(1, 100, 100));
        object3->getComponent<Transform>()->SetScale(Vector3(1, 100, 100));

        object4 = objectFactory->create(Vector3(100, 100, 0));
        object4->getComponent<RigidBody>()->setDynamic(false);
        object4->getComponent<Collider>()->setScale(Vector3(1, 100, 100));
        object4->getComponent<Transform>()->SetScale(Vector3(1, 100, 100));

        object5 = objectFactory->create(Vector3(0, 0, 0));
        object5->getComponent<RigidBody>()->setDynamic(false);
        object5->getComponent<Collider>()->setScale(Vector3(100, 1, 100));
        object5->getComponent<Transform>()->SetScale(Vector3(100, 1, 100));

        auto sphere = objectFactory->create(Vector3(0, 20, 0));
        sphere->getComponent<Collider>()->setScale(Vector3(0));
        sphere->getComponent<Transform>()->SetScale(Vector3(10));
        sphere->getComponent<RenderObject>()->setColor(Vector3(0));
        sphere->getComponent<RigidBody>()->setDynamic(false);
        player = objectFactory->create(Vector3(2));
        player->getComponent<RigidBody>()->setDynamic(false);
        player->getComponent<Collider>()->setScale(Vector3(2));
        player->getComponent<Transform>()->SetScale(Vector3(2));


        objectFactory->setModel(sphere.get(), "C:/.BEbraEngine/src/Models/Sphere.fbx");
        bounds.push_back(object4);
        bounds.push_back(object3);
        bounds.push_back(object2);
        bounds.push_back(object);
        bounds.push_back(sphere);
        globalLight = objectFactory->createDirLight(Vector3(0,-0.5f,0));
        light = objectFactory->createLight(Vector3(0, 20, 0));

        rotate = Vector3(0, -0.5f, 0);
    }


    void GameLogic::clearObjects() {
        if (!objects.empty()) {

            std::shared_ptr<GameObject> obj;
            obj = objects.back();
            objectFactory->destroyObject(obj);
            objects.remove(obj);
            obj.reset();

        }

    }
    void GameLogic::FixedUpdate() {

        if (Input::IsKeyPressed(KEY_CODE::KEY_Z)) {
            auto obj = objectFactory->create(camera->Position + (camera->Front * 5.f));
            obj->getComponent<RigidBody>()->applyImpulse(camera->Front * 40.f, camera->Front);
            Vector3 random_color = Vector3(
                (rand() % 255) / 255.f, (rand() % 255) / 255.f, (rand() % 255) / 255.f
            );
            auto renderobj = obj->getComponent<RenderObject>();
            renderobj->setColor(random_color);
            objects.push_back(obj);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_T)) {
            clearObjects();
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_Q)) {
            lookatobject = true;
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_R)) {
            lookatobject = false;
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_X)) {
            if (objects.size() >= 40)
                posofobject = &objects.back()->getComponent<Transform>()->GetPosition();
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_C)) {
            if (!lights.empty())
            {
                std::shared_ptr<PointLight> light1;
                light1 = lights.front();
                objectFactory->destroyPointLight(light1);
                light1.reset();
                lights.remove(light1);
            }

        }

        if (Input::IsKeyPressed(KEY_CODE::KEY_E)) {
            auto light = objectFactory->createLight(camera->Position);
            Vector3 random_color = Vector3(
                (rand() % 255) / 255.f, (rand() % 255) / 255.f, (rand() % 255) / 255.f
            );
            light->setColor(random_color);
            light->update();
            lights.push_back(light);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_1)) {

            rotate.y = 0.5f;
            globalLight->setDirection(rotate);
        }
        if (Input::IsKeyPressed(KEY_CODE::KEY_2)) {
            rotate.y = -0.5f;
            globalLight->setDirection(rotate);
        }
        for (auto& object : objects) {
            object->getComponent<RigidBody>()->applyImpulseToPoint(1, Vector3(0, 20, 0));
        }

    }
    void GameLogic::Update()
    {
        float speed = 1;
        if (Input::IsKeyPressed(KEY_CODE::KEY_LEFT_SHIFT)) {
            speed = 20;
        }

        //if (Input::IsKeyPressed(KEY_CODE::KEY_Z)) {
        //}
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
        if (lookatobject) {

         //   std::cout << posofobject->x << std::endl;
          //  camera->lookAt(*posofobject);
        }
       // else
            //camera->Update();
        //player->getComponent<Collider>()->setPosition(camera->Position + camera->Front * 15.f);
       // player->getComponent<RigidBody>()->SetPosition(camera->Position);
        //player->getComponent<RigidBody>()->applyImpulse(Vector3(1), Vector3(1));
        //scriptManager->RunScripts();

    }

    GameLogic::~GameLogic()
    {
        //scriptManager.reset();
    }
}