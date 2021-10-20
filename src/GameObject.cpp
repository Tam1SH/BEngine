
#include "GameObject.hpp"
namespace BEbraEngine {
    GameObjectFactory* GameObject::factory;

    void GameObject::_addComponent(std::shared_ptr<AbstractComponent> component)
    {
        Components.push_back(component);
        component->SetParent(this);
    }

    void GameObject::_removeComponent(std::shared_ptr<AbstractComponent> component)
    {
        Components.remove(component);
        component->SetParent(nullptr);
    }

    void GameObject::SetFactory(GameObjectFactory* factory)
    {
        GameObject::factory = factory;
    }

    std::shared_ptr<GameObject> GameObject::New(Vector3& position)
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

    void GameObject::AddComponent(std::shared_ptr<AbstractComponent> component)
    {
        _addComponent(component);
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