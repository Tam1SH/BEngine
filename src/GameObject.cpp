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

    }
    GameObject::GameObject(const std::string& name)
    {
        this->name = name;
    }
    GameObject::~GameObject()
    {
        DEBUG_DESTROY_CHECK("GameObject has not destroyed", this, name, Debug::ObjectType::GameObject, Debug::MessageType::Info);
    }
    void GameObject::destroy(IVisitorGameComponentDestroyer* destroyer)
    {
        for (auto& comp : components_) {
            comp->destroy(destroyer);
        }
        //WARN ёпта - изи рекурсия если плохо пососать.
        destroyer->destroyGameObject(this);
        
    }
}