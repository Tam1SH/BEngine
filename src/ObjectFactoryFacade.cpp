#include "stdafx.h"
#include "ObjectFactoryFacade.hpp"
#include "ScriptState.hpp"
#include "GameObject.hpp"
#include "GameComponent.hpp"
#include "GameObjectFactory.hpp"
#include "Vector3.hpp"
#include "RenderObject.hpp"

using std::unique_ptr;
using std::optional;

namespace BEbraEngine {

    ObjectFactoryFacade::ObjectFactoryFacade(GameObjectFactory* factory)
    {
        realFactory_ = factory;
    }

    void ObjectFactoryFacade::setContext(ScriptState* state)
    {
        state_ = state;
    }

    shared_ptr<GameObject> ObjectFactoryFacade::create(const Vector3& position)
    {
        GameComponentCreateInfo info{};
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
        auto comp = realFactory_->create(info).value();
        state_->addObject(std::static_pointer_cast<GameObject>(comp), info);
        return std::static_pointer_cast<GameObject>(comp);
    }

    shared_ptr<PointLight> ObjectFactoryFacade::createLight(const Vector3& position)
    {
        auto light = realFactory_->createLight(position);
        state_->addLight(light);
        return light;
    }

    shared_ptr<DirectionLight> ObjectFactoryFacade::createDirLight(const Vector3& direction)
    {
        auto light = realFactory_->createDirLight(direction);
        state_->addDirLight(light);
        return light;
    }

    void ObjectFactoryFacade::destroy(shared_ptr<GameObject> object)
    {
        state_->removeObject(object, [=] { realFactory_->destroy(object.get()); });
        
    }


    void ObjectFactoryFacade::destroyPointLight(PointLight* light)
    {
        realFactory_->destroyPointLight(light);
    }

    shared_ptr<SimpleCamera> ObjectFactoryFacade::createCamera(const Vector3& position)
    {
        auto camera = realFactory_->createCamera(position);
        state_->addCamera(camera);
        return camera;
    }

    void ObjectFactoryFacade::destroyCamera(SimpleCamera* camera)
    {
        realFactory_->destroyCamera(camera);
    }

    void ObjectFactoryFacade::setModel(GameObject* object, const string& path)
    {
        realFactory_->setModel(object, path);
    }

}