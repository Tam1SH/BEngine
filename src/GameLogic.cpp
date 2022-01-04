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
#include "ScriptObjectFactory.hpp"
namespace BEbraEngine {


    ScriptState::ScriptState(std::shared_ptr<AbstractRender> render, std::shared_ptr<WorkSpace> workspace, std::shared_ptr<Physics> physics)
    {
        this->physics = physics;
        this->render = render;
        auto scriptsss = new ScriptObjectFactory(new GameObjectFactory(render, physics));
        scriptsss->setContext(this);

        scriptObjectFactory = std::unique_ptr<ScriptObjectFactory>(scriptsss);
        scriptManager = std::make_unique<ScriptManager>(scriptObjectFactory.get());

        scriptManager->LoadScripts();


        scriptInit();
    }

    void ScriptState::scriptInit()
    {
        scriptManager->InitScripts();
        camera = scriptObjectFactory->createCamera(Vector3(1));

        auto object = scriptObjectFactory->create(Vector3(0, 100, -100));
        object->getComponent<RigidBody>()->setDynamic(false);
        object->getComponent<Collider>()->setScale(Vector3(100, 100, 1));
        object->getComponent<Transform>()->setScale(Vector3(100, 100, 1));


        auto object2 = scriptObjectFactory->create(Vector3(0, 100, 100));
        auto d = object2->getComponentByName("RigidBody");
        object2->getComponent<RigidBody>()->setDynamic(false);
        object2->getComponent<Collider>()->setScale(Vector3(100, 100, 1));
        object2->getComponent<Transform>()->setScale(Vector3(100, 100, 1));

        auto object3 = scriptObjectFactory->create(Vector3(-100, 100, 0));
        object3->getComponent<RigidBody>()->setDynamic(false);
        object3->getComponent<Collider>()->setScale(Vector3(1, 100, 100));
        object3->getComponent<Transform>()->setScale(Vector3(1, 100, 100));


        auto object4 = scriptObjectFactory->create(Vector3(100, 100, 0));
        object4->getComponent<RigidBody>()->setDynamic(false);
        object4->getComponent<Collider>()->setScale(Vector3(1, 100, 100));
        object4->getComponent<Transform>()->setScale(Vector3(1, 100, 100));

        auto object5 = scriptObjectFactory->create(Vector3(0, 0, 0));
        object5->getComponent<RigidBody>()->setDynamic(false);
        object5->getComponent<Collider>()->setScale(Vector3(100, 1, 100));
        object5->getComponent<Transform>()->setScale(Vector3(100, 1, 100));

        auto sphere = scriptObjectFactory->create(Vector3(0, 20, 0));
        sphere->getComponent<Collider>()->setScale(Vector3(10));
        sphere->getComponent<Transform>()->setScale(Vector3(10));
        sphere->getComponent<RenderObject>()->setColor(Vector3(1));
        sphere->getComponent<RigidBody>()->setDynamic(false);


        scriptObjectFactory->setModel(sphere.get(), "C:/.BEbraEngine/src/Models/HighSphere.fbx");
        bounds.push_back(object4);
        bounds.push_back(object3);
        bounds.push_back(object2);
        bounds.push_back(object5);
        bounds.push_back(object);
        bounds.push_back(sphere);

        globalLight = scriptObjectFactory->createDirLight(Vector3(0, -0.5f, 0));
        light = scriptObjectFactory->createLight(Vector3(0, 20, 0));
        ///light->setColor(Vector3(0));

        rotate = Vector3(0, -0.5f, 0);
    }


    void ScriptState::clearObjects() {
        if (!objects.empty()) {

            std::shared_ptr<GameObject> obj;
            obj = objects.back();
            scriptObjectFactory->destroyObject(obj);
            objects.remove(obj);
            obj.reset();

        }

    }
    void ScriptState::fixedUpdate() {
        globalLight->setColor(Vector3(0.1));
        //step++;
        //if (step > 127) lightColor.x = 0; else lightColor.x = (128 - step) / 255.f * 2;
        //if(step < 128) lightColor.y = 0; else lightColor.y = (step - 128) / 255.f * 2;
       // if (step < 128) lightColor.z = (1 - lightColor.x); lightColor.z = (1 - lightColor.y);
       // if (step >= 255)
       //     step = 0;
        if (false) {


            auto obj = scriptObjectFactory->create(camera->Position + (camera->Front * 5.f));
            //obj->getComponent<RigidBody>()->applyImpulse(camera->Front * 40.f, camera->Front);
            Vector3 random_color = Vector3(
                (rand() % 255) / 255.f, (rand() % 255) / 255.f, (rand() % 255) / 255.f
            );
            auto renderobj = obj->getComponent<RenderObject>();
            renderobj->setColor(random_color);
            objects.push_back(obj);
        }
        if (Input::isKeyPressed(KEY_CODE::KEY_T)) {
            //clearObjects();
        }

        if (Input::isKeyPressed(KEY_CODE::KEY_C)) {
            if (!lights.empty())
            {
                std::shared_ptr<PointLight> light1;
                light1 = lights.front();
                scriptObjectFactory->destroyPointLight(light1);
                light1.reset();
                lights.remove(light1);
            }

        }

        if (Input::isKeyPressed(KEY_CODE::KEY_E)) {
            auto light = scriptObjectFactory->createLight(camera->Position);
            Vector3 random_color = Vector3(
                (rand() % 255) / 255.f, (rand() % 255) / 255.f, (rand() % 255) / 255.f
            );
            light->setColor(random_color);
            light->update();
            lights.push_back(light);
        }
        if (Input::isKeyPressed(KEY_CODE::KEY_1)) {

            rotate.y = 0.5f;
            globalLight->setDirection(rotate);
        }
        if (Input::isKeyPressed(KEY_CODE::KEY_2)) {
            rotate.y = -0.5f;
            globalLight->setDirection(rotate);
        }

        for (auto& object : objects) {

           
            object->getComponent<RigidBody>()->applyImpulseToPoint(1, Vector3(0, 20, 0));
        }

    }
    void ScriptState::update()
    {
        auto obj = scriptObjectFactory->create(Vector3(0));
        scriptObjectFactory->destroyObject(obj);
     //   scriptManager->runScripts();
        float speed = 1;
        if (Input::isKeyPressed(KEY_CODE::KEY_LEFT_SHIFT)) {
            speed = 20;
        }

        if (Input::isKeyPressed(KEY_CODE::KEY_A)) {
            camera->processKeyboard(LEFT, Time::deltaTime() * speed);
        }
        if (Input::isKeyPressed(KEY_CODE::KEY_D)) {
            camera->processKeyboard(RIGHT, Time::deltaTime() * speed);
        }
        if (Input::isKeyPressed(KEY_CODE::KEY_S)) {
            camera->processKeyboard(BACKWARD, Time::deltaTime() * speed);
        }
        if (Input::isKeyPressed(KEY_CODE::KEY_W)) {
            camera->processKeyboard(FORWARD, Time::deltaTime() * speed);
        }

        static float time = 0;
        time += Time::deltaTime();
        if (time > 1 / 60.f) {
            fixedUpdate();
            time = 0;
        }

    }

    void ScriptState::updateState()
    {
        queues.execute();
    }


    void ScriptState::addObject(shared_ptr<GameObject> object, const GameObject::GameObjectCreateInfo& info)
    {
        queues.addTask([=] {
            
            if (object.get()) {

                auto renderObj = object->getComponent<RenderObject>();
                render->addObject(renderObj);

                if (info.rigidBodyInfo) {
                    auto rigidBody = object->getComponent<RigidBody>();

                    physics->addRigidBody(rigidBody);
                }
            }
            else
                Debug::log("object has destroyed", &object, "", Debug::ObjectType::GameObject, Debug::MessageType::Error);

            }
        );

    }

    void ScriptState::removeObject(shared_ptr<GameObject> object)
    {
        queues.addTask([this, object] {
            if (object.get()) {
               // Debug::log("object removed from render", object->getComponent<RenderObject>().get(), object->getName(), Debug::ObjectType::GameObject, Debug::MessageType::Info);
                physics->removeRigidBody(object->getComponent<RigidBody>());
                render->removeObject(object->getComponent<RenderObject>());
            }
            else
                Debug::log("object pointer is invalid", &object, "", Debug::ObjectType::GameObject, Debug::MessageType::Error);
            });
    }

    void ScriptState::addCamera(shared_ptr<Camera> camera)
    {
        queues.addTask([this, camera] {
            render->addCamera(camera);
            render->selectMainCamera(camera.get());
            });
    }

    void ScriptState::addLight(shared_ptr<PointLight> light)
    {
        queues.addTask([this, light] {
            render->addLight(light);
            });
    }

    void ScriptState::addDirLight(shared_ptr<DirectionLight> light)
    {
        queues.addTask([this, light] {
            render->addGlobalLight(light);
            });
    }

    ScriptState::~ScriptState()
    {
        for (auto& object : bounds) {
            scriptObjectFactory->destroyObject(object);
        }
        for (auto& object : objects) {
            scriptObjectFactory->destroyObject(object);
        }
    }
}