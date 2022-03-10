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
#include "Math.hpp"
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
        camera = scriptObjectFactory->createCamera(Vector3(0, 40, 0));
        
        auto object = scriptObjectFactory->create(Vector3(0, 100, -100));
        object->getComponentChecked<RigidBody>().setDynamic(false);
        object->getComponentChecked<Collider>().setScale(Vector3(100, 100, 1));
        object->getComponentChecked<Transform>().setScale(Vector3(100, 100, 1));
        
        auto object2 = scriptObjectFactory->create(Vector3(0, 100, 100));
        auto d = object2->getComponentByName("RigidBody");
        object2->getComponentChecked<RigidBody>().setDynamic(false);
        object2->getComponentChecked<Collider>().setScale(Vector3(100, 100, 1));
        object2->getComponentChecked<Transform>().setScale(Vector3(100, 100, 1));

        auto object3 = scriptObjectFactory->create(Vector3(-100, 100, 0));
        object3->getComponentChecked<RigidBody>().setDynamic(false);
        object3->getComponentChecked<Collider>().setScale(Vector3(1, 100, 100));
        object3->getComponentChecked<Transform>().setScale(Vector3(1, 100, 100));


        auto object4 = scriptObjectFactory->create(Vector3(100, 100, 0));
        object4->getComponentChecked<RigidBody>().setDynamic(false);
        object4->getComponentChecked<Collider>().setScale(Vector3(1, 100, 100));
        object4->getComponentChecked<Transform>().setScale(Vector3(1, 100, 100));

        auto object5 = scriptObjectFactory->create(Vector3(0, 0, 0));
        object5->getComponentChecked<RigidBody>().setDynamic(false);
        object5->getComponentChecked<Collider>().setScale(Vector3(100, 1, 100));
        object5->getComponentChecked<Transform>().setScale(Vector3(100, 1, 100));

        sphere = scriptObjectFactory->create(Vector3(0, 20, 0));
        scriptObjectFactory->setCollider(sphere->getComponentChecked<Collider>(), Collider::Type::Box);
        sphere->getComponentChecked<Collider>().setScale(Vector3(10));
        sphere->getComponentChecked<Transform>().setScale(Vector3(10));
        sphere->getComponentChecked<RenderObject>().setColor(Vector3(0,0.5,0));
        sphere->getComponentChecked<RigidBody>().setDynamic(false);

        scriptObjectFactory->setModel(*sphere, (boost::filesystem::current_path() / "Models/Box.fbx").string());
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


            Quaternion quat;
            quat = BEbraMath::rotate(quat, 45, Vector3(0, 1, 0));
            // obj->getComponentChecked<Collider>().setPosition(Vector3(0, 80, 0));
           //  obj->getComponentChecked<Transform>().setPosition(Vector3(0, 80, 0));
             //obj->getComponentChecked<RigidBody>().setPosition(Vector3(0, 80, 0));
        }

    }

    std::mt19937::result_type seed = time(0);
    auto dice_rand = std::bind(std::uniform_int_distribution<int>(1, 3),
        std::mt19937(seed));

    auto getPath(int rand) {

        auto path = (boost::filesystem::current_path() / "Models");

        switch (rand) {
        case 1: return path / "Box.fbx";
        case 2: return path / "Cylinder.fbx";
        case 3: return path / "Sphere.fbx";
        }

    }



    Collider::Type getShape(int rand) {

        switch (rand) {
        case 1: return Collider::Type::Box;
        //case 2: return Collider::Type::Capsule;
        //case 3: return Collider::Type::Cone;
        case 2: return Collider::Type::Cylinder;
        case 3: return Collider::Type::Sphere;

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

        if (Input::isKeyPressed(KEY_CODE::KEY_G)) {
            int rand = dice_rand();
            auto obj = scriptObjectFactory->create(Vector3(0, 40, 0));
            
            scriptObjectFactory->setCollider(obj->getComponentChecked<Collider>(), getShape(rand));
            scriptObjectFactory->setModel(*obj, getPath(rand).string());
         //   scriptObjectFactory->setTexture(*obj, boost::filesystem::current_path() / "pizda.jpg");
            obj->getComponentChecked<RenderObject>().setColor(Vector3(1));
            obj->getComponentChecked<Collider>().setScale(Vector3(2));
            obj->getComponentChecked<Transform>().setScale(Vector3(2));
            Quaternion quat;
            quat = BEbraMath::rotate(quat, 45, Vector3(0, 1, 0));
           // obj->getComponentChecked<Collider>().setPosition(Vector3(0, 80, 0));
          //  obj->getComponentChecked<Transform>().setPosition(Vector3(0, 80, 0));
            //obj->getComponentChecked<RigidBody>().setPosition(Vector3(0, 80, 0));
            obj->getComponentChecked<RigidBody>().setRotation(quat);
            objects.push_back(obj);
        }


        if (Input::isKeyPressed(KEY_CODE::KEY_H)) {
            if (objects.size() != 0) {

                auto obj = objects.back();
                scriptObjectFactory->destroy(obj);
                objects.remove(obj);
            }
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

       // render->drawLine(camera->Front + camera->Position, (Vector3(0, 0, 1) / 20 + camera->Position), Vector3(1, 0, 0));
       // render->drawLine(camera->Front + camera->Position, (Vector3(0, 1, 0) / 20 + camera->Position), Vector3(0, 1, 0));
       // render->drawLine(camera->Front + camera->Position, (Vector3(1, 0, 0) / 20 + camera->Position), Vector3(0, 0, 1));

    }

    void ScriptState::updateState()
    {
        queues.execute();
    }


    void ScriptState::addObject(shared_ptr<GameObject> object, const GameComponentCreateInfo& info)
    {

        auto pObject = object;
        queues.addTask(ExecuteType::Single, 
            [=] {
                auto& renderObj = pObject->getComponentChecked<RenderObject>();
                render->addObject(renderObj);

                if (info.rigidBodyInfo) {
                    auto& rigidBody = pObject->getComponentChecked<RigidBody>();

                    physics->addRigidBody(rigidBody);
                }
                objects_.push_back(object);

                // бля что ита
                const GameObject* const bulshit = &*object;
                tbb::concurrent_hash_map<const GameObject*, shared_ptr<GameObject>>::const_accessor a{};
                objectsCache.insert({ bulshit, object});
            }
            

        );

    }

    void ScriptState::removeObject(shared_ptr<GameObject> object,

        std::function<void(GameObject&)> callback)
    {
        queues.addTask(ExecuteType::Single,
             [this, object, callback] () {
                physics->removeRigidBody(object->getComponentChecked<RigidBody>());
                render->removeObject(object->getComponentChecked<RenderObject>());
                std::remove(objects_.begin(), objects_.end(), object);
               
                callback(*object);
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

    void ScriptState::addLight(Light& light)
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

    shared_ptr<GameObject> ScriptState::getShared(const GameObject& object)
    {
        auto sObj = shared_ptr<GameObject>();
        tbb::concurrent_hash_map<const GameObject*, shared_ptr<GameObject>>::accessor a{};

        if (objectsCache.find(a, &object)) 
            return a->second;
        else 
            throw std::runtime_error("the object is not registered");
        
    }

    ScriptState::~ScriptState()
    {
        for (auto& object : bounds) {
            scriptObjectFactory->destroy(object);
        }
        for (auto& object : objects) {
            scriptObjectFactory->destroy(object);
        }
    }
}