#include "stdafx.h"
#include "ObjectFactoryFacade.hpp"
#include "ScriptState.hpp"
#include "GameObject.hpp"
#include "GameComponent.hpp"
#include "GameObjectFactory.hpp"
#include "Vector3.hpp"
#include "RenderObject.hpp"
#include "Camera.hpp"
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

    void ObjectFactoryFacade::destroyComponent(GameComponent& component)
    {
        realFactory_->destroy(component);
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
        colliderInfo.type = Collider::Type::Box;

        rigidBodyInfo.mass = 1.f;
        rigidBodyInfo.position = transformInfo.position;

        info.colliderInfo = &colliderInfo;
        info.renderInfo = &renderInfo;
        info.transformInfo = &transformInfo;
        info.rigidBodyInfo = &rigidBodyInfo;
        
        auto opt_comp = realFactory_->create(info);
        if (opt_comp.has_value()) {
            auto obj = dynamic_cast<GameObject*>(opt_comp.value());
            if (obj) {
                auto sObj = shared_ptr<GameObject>(obj);
                state_->addObject(sObj, info);
                return sObj;
            }
            else throw std::exception();
        }
        else throw std::exception();

    }

    shared_ptr<Light> ObjectFactoryFacade::createLight(const Vector3& position)
    {
        auto light = realFactory_->createLight(position);
        state_->addLight(*light);
        return light;
    }

    shared_ptr<DirectionLight> ObjectFactoryFacade::createDirLight(const Vector3& direction)
    {
        auto light = realFactory_->createDirLight(direction);
        state_->addDirLight(*light);
        return light;
    }

    void ObjectFactoryFacade::destroy(shared_ptr<GameObject>& object)
    {
        state_->removeObject(object, [=](GameObject& obj) { realFactory_->destroy(obj); });
    }


    void ObjectFactoryFacade::destroyPointLight(Light& light)
    {
        realFactory_->destroyPointLight(light);
    }

    shared_ptr<SimpleCamera> ObjectFactoryFacade::createCamera(const Vector3& position)
    {
        auto camera = realFactory_->createCamera(position);
        state_->addCamera(*camera);
        return camera;
    }

    void ObjectFactoryFacade::destroyCamera(SimpleCamera& camera)
    {
        realFactory_->destroyCamera(camera);
    }

    void ObjectFactoryFacade::setModel(GameObject& object, const string& path)
    {
        realFactory_->setModel(object, path);
    }

    void ObjectFactoryFacade::setCollider(Collider& col, Collider::Type type)
    {
        realFactory_->setCollider(col, type);
    }

    void ObjectFactoryFacade::setTexture(GameObject& object, const boost::filesystem::path& path)
    {
        realFactory_->setTexture(object, path);
    }

}