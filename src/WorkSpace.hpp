#pragma once
#include "AbstractComponent.hpp"
#include <list>
#include "GameObject.hpp"
//TODO: ну хуй знает, а есть толк от этого?
namespace BEbraEngine {
    class WorkSpace : public GameObjectComponent {
    public:

        std::list<std::shared_ptr<GameObjectComponent>>& GetList() {
            return Components;
        }
        std::shared_ptr<GameObject> FindObject(GameObject* object) {
            auto _object = static_cast<GameObjectComponent*>(object);
            for (auto component : Components) {
                if (_object == component.get()) {
                    return std::static_pointer_cast<GameObject>(component);
                }


            }
        }
        std::shared_ptr<GameObject> FindObject(GameObjectComponent* object) {
            for (auto component : Components) {
                if (object == component.get()) {
                    return std::static_pointer_cast<GameObject>(component);
                }
            }
            throw std::exception();
        }
        std::shared_ptr<GameObject> FindObject(std::string name) {
            for (auto component : Components) {
                if (name == component->GetName()) {
                    return std::static_pointer_cast<GameObject>(component);
                }
            }
        }
        void RemoveAll() {
            Components.clear();
        }
        WorkSpace() {
            name = "Workspace";
        }
        ~WorkSpace() {
            RemoveAll();
        }
    };
}

