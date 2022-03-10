#include "stdafx.h"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include "Debug.hpp"
#include "IVisitorGameComponentDestroyer.hpp"
namespace BEbraEngine {
    GameComponent* GameObject::getComponentByName(const string& name) const noexcept
    {
        for (auto& component : components_) {

            //TODO: нестрогое сравнение названий классов, в будущем могу на этом пососать.
            const string componentName = typeid(*component).name();

            if (componentName.find(name) != string::npos) {
                return component.get();
            }
        }
        return nullptr;
    }
    bool GameObject::isComposite() const noexcept
    {
        return true;
    }

    GameObject::GameObject() noexcept
    {
        name_ = "GameObject";

    }
    GameObject::GameObject(const string& name) noexcept
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