#include "stdafx.h"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include "Debug.hpp"
namespace BEbraEngine {

    bool GameObject::isComposite() const
    {
        return true;
    }

    GameObject::GameObject()
    {
        name = "GameObject";
#ifdef _DEBUG
        Debug::log("Create", this, name, Debug::ObjectType::GameObject, Debug::MessageType::Info);
#endif 

    }
    GameObject::GameObject(const std::string& name)
    {
#ifdef _DEBUG
        Debug::log("Create", this, name, Debug::ObjectType::GameObject, Debug::MessageType::Info);
#endif 
    }
    GameObject::~GameObject()
    {
#ifdef _DEBUG
        Debug::log("Destroy", this, name, Debug::ObjectType::GameObject, Debug::MessageType::Info);
#endif 
    }
}