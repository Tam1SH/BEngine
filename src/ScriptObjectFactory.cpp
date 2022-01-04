#include "stdafx.h"
#include "ScriptObjectFactory.hpp"
#include "GameObject.hpp"
#include "Vector3.hpp"
#include "GameObjectFactory.hpp"
#include "GameLogic.hpp"

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace BEbraEngine {

    ScriptObjectFactory::ScriptObjectFactory(GameObjectFactory* factory)
    {
        realFactory_ = factory;
    }

    void ScriptObjectFactory::setContext(ScriptState* logic)
    {
        logic_ = logic;
    }

    shared_ptr<GameObject> ScriptObjectFactory::create(const Vector3& position)
    {
        GameObject::GameObjectCreateInfo info{};
        Transform::TransformCreateInfo transformInfo{};
        Collider::ColliderCreateInfo colliderInfo{};
        RigidBody::RigidBodyCreateInfo rigidBodyInfo{};
        RenderObject::RenderObjectCreateInfo renderInfo{};

        transformInfo.position = position;

        colliderInfo.position = position;
        colliderInfo.scale = transformInfo.scale;
        colliderInfo.type = Collider::ColliderCreateInfo::Type::Box;

        rigidBodyInfo.mass = 1.f;
        rigidBodyInfo.position = transformInfo.position;

        info.colliderInfo = &colliderInfo;
        info.renderInfo = &renderInfo;
        info.transformInfo = &transformInfo;
        info.rigidBodyInfo = &rigidBodyInfo;
        return create(info).value();
    }

    optional<shared_ptr<GameObject>> ScriptObjectFactory::create(const GameObject::GameObjectCreateInfo& info)
    {
        auto optObj = realFactory_->create(info);

        if (optObj.has_value()) {
            auto obj = optObj.value();
            logic_->addObject(obj, info);
        }


        return optObj;
    }

    shared_ptr<PointLight> ScriptObjectFactory::createLight(const Vector3& position)
    {
        auto light = realFactory_->createLight(position);
        logic_->addLight(light);
        return light;
    }

    shared_ptr<DirectionLight> ScriptObjectFactory::createDirLight(const Vector3& direction)
    {
        auto light = realFactory_->createDirLight(direction);
        logic_->addDirLight(light);
        return light;
    }

    void ScriptObjectFactory::destroyObject(shared_ptr<GameObject> object)
    {
        logic_->removeObject(object);
        realFactory_->destroyObject(object);
    }


    void ScriptObjectFactory::destroyPointLight(shared_ptr<PointLight> light)
    {
        realFactory_->destroyPointLight(light);
    }

    shared_ptr<Camera> ScriptObjectFactory::createCamera(const Vector3& position)
    {
        auto camera = realFactory_->createCamera(position);
        logic_->addCamera(camera);
        return camera;
    }

    void ScriptObjectFactory::destroyCamera(shared_ptr<Camera> camera)
    {
        realFactory_->destroyCamera(camera);
    }

    void ScriptObjectFactory::setModel(GameObject* object, const string& path)
    {
        realFactory_->setModel(object, path);
    }

}