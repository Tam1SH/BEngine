#include "stdafx.h"
#include "ScriptState.hpp"
#include "ScriptManager.hpp"
#include "Time.hpp"
#include "Camera.hpp"
#include "Physics.hpp"
#include "Input.hpp"
#include "ObjectFactoryFacade.hpp"
#include "AbstractRender.hpp"
#include "GameObjectFactory.hpp"
#include "RenderObject.hpp"
#include "GameObject.hpp"
namespace BEbraEngine {


    ScriptState::ScriptState(AbstractRender& render, Physics& physics)
    {
        this->physics = &physics;
        this->render = &render;
        auto scriptsss = new ObjectFactoryFacade(new GameObjectFactory(render, physics));
        scriptsss->setContext(this);

        scriptObjectFactory = std::unique_ptr<ObjectFactoryFacade>(scriptsss);
        scriptManager = std::unique_ptr<ScriptManager>(new ScriptManager(scriptObjectFactory.get()));

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


        scriptObjectFactory->setModel(*sphere, "C:/.BEbraEngine/src/Models/HighSphere.fbx");


        globalLight = scriptObjectFactory->createDirLight(Vector3(0, -0.5f, 0));
        light = scriptObjectFactory->createLight(Vector3(0, 20, 0));
        ///light->setColor(Vector3(0));

        rotate = Vector3(0, -0.5f, 0);
    }


    void ScriptState::clearObjects() { }

    void ScriptState::fixedUpdate() {
        globalLight->setColor(Vector3(0.1));
        //step++;
        //if (step > 127) lightColor.x = 0; else lightColor.x = (128 - step) / 255.f * 2;
        //if(step < 128) lightColor.y = 0; else lightColor.y = (step - 128) / 255.f * 2;
       // if (step < 128) lightColor.z = (1 - lightColor.x); lightColor.z = (1 - lightColor.y);
       // if (step >= 255)
       //     step = 0;

        if (Input::isKeyPressed(KEY_CODE::KEY_T)) {
            //clearObjects();
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
        //auto obj = scriptObjectFactory->create(Vector3(0));
        //scriptObjectFactory->destroy(obj);
        scriptManager->runScripts();
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


    void ScriptState::addObject(GameObject& object, const GameComponentCreateInfo& info)
    {
        auto pObject = &object;
        queues.addTask(ExecuteType::Single, 
            [=] {
                auto renderObj = pObject->getComponent<RenderObject>();
                render->addObject(*renderObj);

                if (info.rigidBodyInfo) {
                    auto rigidBody = pObject->getComponent<RigidBody>();

                    physics->addRigidBody(*rigidBody);
                }
            }
            
        );

    }

    void ScriptState::removeObject(GameObject& object,

        std::function<void(GameObject&)> callback)
    {
        auto pObject = &object;
        queues.addTask(ExecuteType::Single,
             [this, pObject, callback] () {
                physics->removeRigidBody(*pObject->getComponent<RigidBody>());
                render->removeObject(*pObject->getComponent<RenderObject>());
                callback(*pObject);
            });
            
    }

    void ScriptState::addCamera(SimpleCamera& camera)
    {
        auto pCamera = &camera;
        queues.addTask(ExecuteType::Single,
            [=] {
            render->addCamera(*pCamera);
            render->selectMainCamera(*pCamera);
            }
        );
    }

    void ScriptState::addLight(PointLight& light)
    {
        auto pLight = &light;
        queues.addTask(ExecuteType::Single,
            [=] {
            render->addLight(*pLight);
            }
        );
    }

    void ScriptState::addDirLight(DirectionLight& light)
    {
        auto pLight = &light;
        queues.addTask(ExecuteType::Single,
            [=] {
            render->addGlobalLight(*pLight);
            }
        );
    }

    ScriptState::~ScriptState()
    {
        for (auto& object : bounds) {
            scriptObjectFactory->destroy(*object);
        }
        for (auto& object : objects) {
            scriptObjectFactory->destroy(*object);
        }
    }
}