#include "stdafx.h"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
namespace BEbraEngine {
    GameObjectFactory* GameObject::factory;


    void GameObject::SetFactory(GameObjectFactory* factory)
    {
        GameObject::factory = factory;
    }

    std::shared_ptr<GameObject> GameObject::New(const Vector3& position)
    {
        return GameObject::factory->Create(position);
    }

    void GameObject::Destroy(std::shared_ptr<GameObject> object)
    {
        factory->Destroy(object);
    }

    void GameObject::Destroy()
    {
        factory->Destroy(this);
    }


    bool GameObject::IsComposite() const
    {
        return true;
    }

    GameObject::GameObject()
    {
        name = "GameObject";
        std::cout << "GAMEOBJECT CREATED " << this << std::endl;
    }

    GameObject::~GameObject()
    {

        std::cout << "GAMEOBJECT DESTROYED " << this << std::endl;
        factory->Destroy(this);
    }
}