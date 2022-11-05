export module GameObject_impl;
import GameObject;
import <typeinfo>;
import <string>;
using std::string;

namespace BEbraEngine {
    


    GameObject::GameObject() noexcept
    {
        name_ = "GameObject";
    }
    bool GameObject::isComposite() const noexcept
    {
        return true;

    }
    GameComponent* GameObject::getComponentByName(const string& name) const noexcept
    {
        for (auto& component : components_) {

            //TODO: нестрогое сравнение == выстрел в ногу.
            const std::string componentName = typeid(*component).name();

            if (componentName.find(name) != string::npos) {
                return component.get();
            }
        }
        return nullptr;
    }
}