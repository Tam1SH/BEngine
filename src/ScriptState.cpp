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
#include "VulkanRender.hpp"
#include "CreateInfoStructures.hpp"
#include "VulkanObjects.hpp"
#include "BaseRenderWindow.hpp"
namespace BEbraEngine {

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



    ScriptState::ScriptState(AbstractRender& render, Physics& physics, BaseWindow& window)
    {
        this->physics = &physics;
        this->render = &render;
        this->window = &window;
        renderWorld = std::make_unique<RenderWorld>(render);
        auto scriptsss = new ObjectFactoryFacade(new GameObjectFactory(render, physics, *renderWorld));
        scriptsss->setContext(this);
        render.setWorld(*renderWorld);
        scriptObjectFactory = std::unique_ptr<ObjectFactoryFacade>(scriptsss);
        scriptManager = std::unique_ptr<ScriptManager>(new ScriptManager(scriptObjectFactory.get()));

        scriptManager->LoadScripts();


        scriptInit();
    }

    void ScriptState::scriptInit()
    {

        scriptManager->InitScripts();
        camera = scriptObjectFactory->createCamera(Vector3(0, 40, 0));
        
        player = scriptObjectFactory->create(Vector3(-30, 30, 0));
        player->getComponentChecked<Transform>().setScale(Vector3(2));
        player->getComponentChecked<Collider>().setScale(Vector3(2));
        scriptObjectFactory->setMaterialAsync(player, { boost::filesystem::current_path() / "textures" / "textureTest.jpg",
                                                    boost::filesystem::current_path() / "textures" / "specularTest.jpg", 
                                                    boost::filesystem::current_path() / "textures" / "normalTest.jpg" });

        auto& body = player->getComponentChecked<RigidBody>();
        body.setMaxVelocity(20);
        body.lockRotateX(true);
        body.lockRotateY(true);
        body.lockRotateZ(true);

        auto object = scriptObjectFactory->create(Vector3(-30, 20, 0));
        object->getComponentChecked<RigidBody>().setDynamic(false);
        object->getComponentChecked<Collider>().setScale(Vector3(20, 1, 20));
        object->getComponentChecked<Transform>().setScale(Vector3(20, 1, 20));

        auto object1 = scriptObjectFactory->create(Vector3(30, 20, 0));
        object1->getComponentChecked<RigidBody>().setDynamic(false);
        object1->getComponentChecked<Collider>().setScale(Vector3(20, 1, 20));
        object1->getComponentChecked<Transform>().setScale(Vector3(20, 1, 20));

        auto object2 = scriptObjectFactory->create(Vector3(0, 20, 30));
        object2->getComponentChecked<RigidBody>().setDynamic(false);
        object2->getComponentChecked<Collider>().setScale(Vector3(60, 1, 20));
        object2->getComponentChecked<Transform>().setScale(Vector3(60, 1, 20));

        auto object3 = scriptObjectFactory->create(Vector3(0, 20, -30));
        object3->getComponentChecked<RigidBody>().setDynamic(false);
        object3->getComponentChecked<Collider>().setScale(Vector3(60, 1, 20));
        object3->getComponentChecked<Transform>().setScale(Vector3(60, 1, 20));
        
        /*
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
        */

        /*
        auto object6 = scriptObjectFactory->create(Vector3(0, 60, 0));
        object6->getComponentChecked<RigidBody>().setDynamic(false);
        object6->removeComponent(object6->getComponentCheckedPtr<Collider>());
        object6->removeComponent(object6->getComponentCheckedPtr<RigidBody>());

        object6->getComponentChecked<Transform>().setScale(Vector3(10));
        scriptObjectFactory->setModel(*object6, (boost::filesystem::current_path() / "Models/Sphere.fbx").string());
        */


       // scriptObjectFactory->setModel(*sphere, (boost::filesystem::current_path() / "Models/Box.fbx").string());
        globalLight = scriptObjectFactory->createDirLight(Vector3(0, -0.5f, 0));

        auto object6 = scriptObjectFactory->create(Vector3(20, 33, 0));
        object6->getComponentChecked<RigidBody>().setDynamic(false);
        auto col = object6->getComponentCheckedPtr<Collider>();
        auto body1 = object6->getComponentCheckedPtr<RigidBody>();

        object6->removeComponent(col);
        object6->removeComponent(body1);
        scriptObjectFactory->destroy(*col);
        scriptObjectFactory->destroy(*body1);

        object6->getComponentChecked<Transform>().setScale(Vector3(2));
        scriptObjectFactory->setModel(*object6, (boost::filesystem::current_path() / "Models/Sphere.fbx").string());

        light = scriptObjectFactory->createLight(Vector3(-20, 25, 0));
        lights.push_back(light);
        light->setColor(Vector3(1,0,0));
        light = scriptObjectFactory->createLight(Vector3(20, 25, 0));

        lights.push_back(light);

        light->setColor(Vector3(0, 1, 0));
        light = scriptObjectFactory->createLight(Vector3(0, 25, 20));

        lights.push_back(light);
        light->setColor(Vector3(0, 0, 1));

        rotate = Vector3(0, -0.5f, 0);

    }


    void ScriptState::clearObjects() { }

    void ScriptState::fixedUpdate() {
        globalLight->setColor(Vector3(0));
        //step++;
        //if (step > 127) lightColor.x = 0; else lightColor.x = (128 - step) / 255.f * 2;
        //if(step < 128) lightColor.y = 0; else lightColor.y = (step - 128) / 255.f * 2;
       // if (step < 128) lightColor.z = (1 - lightColor.x); lightColor.z = (1 - lightColor.y);
       // if (step >= 255)
       //     step = 0;

        if (Input::isKeyPressed(KeyCode::KEY_T)) {
            auto& mat = player->getComponentChecked<Material>();
            static_cast<VulkanRender*>(render)->getBitMapFromSwapChainImage();
            //clearObjects();
        }

        if (Input::isKeyPressed(KeyCode::KEY_F11))
        {
           // static bool b{};
           // b = !b;
           // if(b)
                window->setFullScreen(BaseWindow::FullScreenType::FullScreenOnWindow);
           // else 
            //    window->setFullScreen(BaseWindow::FullScreenType::None);

        }
        if (Input::isKeyPressed(KeyCode::KEY_1)) {

            rotate.y = 0.5f;
            globalLight->setDirection(rotate);
        }
        if (Input::isKeyPressed(KeyCode::KEY_2)) {
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


    void ScriptState::update()
    {
        //auto obj = scriptObjectFactory->create(Vector3(0));
        //scriptObjectFactory->destroy(obj);
        auto pos = player->getComponentChecked<Transform>().getPosition();
       // pos.y += 10;
        //camera->moveTo(pos);

        scriptManager->runScripts();
        float speed = 1;
        if (Input::isKeyPressed(KeyCode::KEY_LEFT_SHIFT)) {
            speed = 20;
        }

        if (Input::isKeyPressed(KeyCode::KEY_G)) {
            int rand_ = dice_rand();
            auto obj = scriptObjectFactory->create(Vector3(0, 40, 0));
            
            scriptObjectFactory->setCollider(obj->getComponentChecked<Collider>(), getShape(rand_));
            //scriptObjectFactory->setModel(*obj, getPath(rand_).string());

            
            obj->getComponentChecked<RenderObject>().setColor(Vector3((rand() % 256) / (float)256, rand() % 256 / (float)256, rand() % 256 / (float)256));
            /*
            
            scriptObjectFactory->setMaterialAsync(obj, { boost::filesystem::current_path() / "textures" / "textureTest.jpg",
                                             boost::filesystem::current_path() / "textures" / "specularTest.jpg",
                                             boost::filesystem::current_path() / "textures" / "normalTest.jpg" });
                                             */
            
            Quaternion quat;
            objects.push_back(obj);
        }

        if (Input::isKeyPressed(KeyCode::KEY_Q)) {
            camera->moveTo(Vector3(0, 40, 0));
        }
        
            for (auto& object : objects) {

                auto& rigidBody = object->getComponentChecked<RigidBody>();

                //direction = BEbraMath::normalize(*pos - Vector3(0, 30, 10));

                //rigidBody.applyExplosionImpulse(100,10, Vector3(0,60,0));
            }
        
        for (auto& object : objects) {

         //   auto& body = object->getComponentChecked<RigidBody>();
         //   auto pos1 = body.getTransform().getPosition();
        ///    auto dirc = body.getVelocity();
        //    render->drawLine(pos1, (dirc + pos1), Vector3(1));
        }


        
        if (Input::isKeyPressed(KeyCode::KEY_H)) {
            if (objects.size() != 0) {

                auto obj = objects.back();
                scriptObjectFactory->destroy(obj);
                objects.remove(obj);
            }
        }   
        static bool inFly = false;

        auto& rigidBodyPlayer = player->getComponentChecked<RigidBody>();
        if (Input::isKeyPressed(KeyCode::KEY_T)) {
            //rigidBodyPlayer.moveTo(Vector3(-30, 30, 0));
        }
        if (Input::isKeyPressed(KeyCode::KEY_A) && !inFly) {
            camera->processKeyboard(LEFT, Time::deltaTime() * speed);
            auto pos = camera->Right;
            pos.y = 0;
            rigidBodyPlayer.applyImpulse(-pos, (camera->Right * Time::deltaTime() * speed));
        }
        if (Input::isKeyPressed(KeyCode::KEY_D) && !inFly ) {
            camera->processKeyboard(RIGHT, Time::deltaTime() * speed);
            auto pos = camera->Right;
            pos.y = 0;
            rigidBodyPlayer.applyImpulse(pos, (camera->Right * Time::deltaTime() * speed));
        }
        if (Input::isKeyPressed(KeyCode::KEY_S) && !inFly) {
            camera->processKeyboard(BACKWARD, Time::deltaTime() * speed);
            auto pos = camera->Front;
            pos.y = 0;
            rigidBodyPlayer.applyImpulse(-pos, (camera->Front * Time::deltaTime() * speed));
        }
        if (Input::isKeyPressed(KeyCode::KEY_F)) {
            auto pos = camera->Position;
            pos.y -= 1;
            rigidBodyPlayer.applyExplosionImpulse(10, 10, pos);
        }
        if (Input::isKeyPressed(KeyCode::KEY_W) && !inFly) {
            camera->processKeyboard(FORWARD, Time::deltaTime() * speed);
            auto pos = camera->Front;
            pos.y = 0;
            rigidBodyPlayer.applyImpulse(pos, (camera->Front * Time::deltaTime() * speed));
        }
        static float y = 0;

        //y = rigidBodyPlayer.getVelocity().y;
        if (y <= 0.01 && y >= 0)
        {
            inFly = false;
            if (Input::isKeyPressed(KeyCode::KEY_SPACE)) {
                auto pos = camera->Up;
               // pos.x = rigidBodyPlayer.getVelocity().x;
               // pos.z = rigidBodyPlayer.getVelocity().y;
                pos.y = 20;
               // rigidBodyPlayer.applyImpulse(pos, (pos * Time::deltaTime() * speed));
                
            }
        }
        else inFly = true;
        inFly = false;
        static float time = 0;
        time += Time::deltaTime();
        if (time > 1 / 60.f) {
            fixedUpdate();
            time = 0;
        }
        static float time1 = 0;
        static float count = 0;
        time1 += Time::deltaTime();
        if (time1 > 0.001) {
            if (count < 0) {
                DEBUG_LOG1(std::to_string(count));

                int rand = dice_rand();
                auto obj = scriptObjectFactory->create(Vector3(0, 200, 0));

                scriptObjectFactory->setCollider(obj->getComponentChecked<Collider>(), getShape(rand));
                scriptObjectFactory->setModel(*obj, getPath(rand).string());
                //   scriptObjectFactory->setTexture(*obj, boost::filesystem::current_path() / "pizda.jpg");
                obj->getComponentChecked<RenderObject>().setColor(Vector3(1));

                //auto collider = obj->removeComponent(obj->getComponentCheckedPtr<Collider>());
                //auto rigidbody = obj->removeComponent(obj->getComponentCheckedPtr<RigidBody>());
                //scriptObjectFactory->destroyComponent(*collider);
               // scriptObjectFactory->destroyComponent(*rigidbody);

               // obj->getComponentChecked<Transform>().setScale(Vector3(2));
                Quaternion quat;
                quat = BEbraMath::rotate(quat, 45, Vector3(0, 1, 0));
                // obj->getComponentChecked<Collider>().setPosition(Vector3(0, 80, 0));
               //  obj->getComponentChecked<Transform>().setPosition(Vector3(0, 80, 0));
                 //obj->getComponentChecked<RigidBody>().setPosition(Vector3(0, 80, 0));
                 //obj->getComponentChecked<RigidBody>().setRotation(quat);
                objects.push_back(obj);
                time1 = 0;
                count++;
            }
        }
        for (auto& object : objects) {
            auto pos = object->getComponentChecked<Transform>().getPosition();
            auto& body = object->getComponentChecked<RigidBody>();
            if (pos.y < 0) {
                body.moveTo(Vector3(pos.x, 110, pos.z));
            }
            //if (pos.y > 110) {
            //    body.moveTo(Vector3(pos.x, 0, pos.z));
           // }

            if (pos.x > 10) {
                body.moveTo(Vector3(-10, pos.y, pos.z));
            }
            if (pos.x < -10) {
                body.moveTo(Vector3(10, pos.y, pos.z));
            }

            if (pos.z > 10) {
                body.moveTo(Vector3(pos.x, pos.y, -10));
            }
            if (pos.z < -10) {
                body.moveTo(Vector3(pos.x, pos.y, 10));
            }
        }
       // render->drawLine(camera->Front + camera->Position, (Vector3(0, 0, 1) / 20 + camera->Position), Vector3(1, 0, 0));
       // render->drawLine(camera->Front + camera->Position, (Vector3(0, 1, 0) / 20 + camera->Position), Vector3(0, 1, 0));
       // render->drawLine(camera->Front + camera->Position, (Vector3(1, 0, 0) / 20 + camera->Position), Vector3(0, 0, 1));

    }

    void ScriptState::updateState()
    {
        renderWorld->update();
        queues.execute();
    }


    void ScriptState::addObject(shared_ptr<GameObject> object)
    {
        queues.addTask(ExecuteType::Single, 
            [=] {
                auto renderObj = object->getComponent<RenderObject>();
                if (renderObj.has_value()) {
                    renderWorld->addObject(object->getComponentChecked<RenderObject>());
                }
                else
                    DEBUG_LOG1("Object has no component 'RenderObject'");
                

                auto rigidBody = object->getComponent<RigidBody>();
                if (rigidBody.has_value()) {
                    physics->addRigidBody(object->getComponentChecked<RigidBody>());
                }
                else
                    DEBUG_LOG1("Object has no component 'RigidBody'");

                objects_.push_back(object);
            }
            

        );

    }

    void ScriptState::removeObject(shared_ptr<GameObject> object,

        std::function<void(GameObject&)> callback)
    {
        queues.addTask(ExecuteType::Single,
             [this, object, callback] () {

                auto renderObj = object->getComponent<RenderObject>();
                if (renderObj.has_value()) {
                    renderWorld->removeObject(object->getComponentChecked<RenderObject>());
                }
                else
                    DEBUG_LOG1("Object has no component 'RenderObject'");

                auto rigidBody = object->getComponent<RigidBody>();
                if (rigidBody.has_value()) {
                    physics->removeRigidBody(object->getComponentChecked<RigidBody>());
                }
                else
                    DEBUG_LOG1("Object has no component 'RigidBody'");

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
            renderWorld->addLight(*pLight);
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
            scriptObjectFactory->destroy(object);
        }
        for (auto& object : objects) {
            scriptObjectFactory->destroy(object);
        }
    }
}