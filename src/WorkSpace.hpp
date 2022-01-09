#pragma once
#include "GameComponent.hpp"
#include <list>
#include "GameObject.hpp"
//TODO: ну хуй знает, а есть толк от этого?
namespace BEbraEngine {
    class WorkSpace : public GameComponent {
    public:

        std::list<std::shared_ptr<GameComponent>>& GetList() {
            return components_;
        }
        std::shared_ptr<GameObject> FindObject(GameObject* object) {
            auto _object = static_cast<GameComponent*>(object);
            for (auto component : components_) {
                if (_object == component.get()) {
                    return std::static_pointer_cast<GameObject>(component);
                }


            }
        }
        std::shared_ptr<GameObject> FindObject(GameComponent* object) {
            for (auto component : components_) {
                if (object == component.get()) {
                    return std::static_pointer_cast<GameObject>(component);
                }
            }
            throw std::exception();
        }
        std::shared_ptr<GameObject> FindObject(std::string name) {
            for (auto component : components_) {
                if (name == component->getName()) {
                    return std::static_pointer_cast<GameObject>(component);
                }
            }
        }
        void RemoveAll() {
            components_.clear();
        }
        WorkSpace() {
            name = "Workspace";
        }
        ~WorkSpace() {
            RemoveAll();
        }

        // Унаследовано через GameObjectComponent
        virtual void destroy(IVisitorGameComponentDestroyer* destroyer) override;
    };
}

