#include "stdafx.h"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include "Debug.hpp"
#include "IVisitorGameComponentDestroyer.hpp"
namespace BEbraEngine {

    bool GameObject::isComposite() const
    {
        return true;
    }

    GameObject::GameObject()
    {
        name_ = "GameObject";

    }
    GameObject::GameObject(const string& name)
    {
        this->name_ = name;
    }
    GameObject::~GameObject()
    {
        DEBUG_DESTROY_CHECK("GameObject has not destroyed", this, name_, Debug::ObjectType::GameObject, Debug::MessageType::Info);
    }

    void GameObject::destroy(IVisitorGameComponentDestroyer& destroyer)
    {
        for (auto& comp : components_) {
            comp->destroy(destroyer);
        }

        destroyer.destroyGameObject(*this);
        
    }
}