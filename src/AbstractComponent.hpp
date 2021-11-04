#pragma once
#include <memory>
#include <string>
#include <list>
namespace BEbraEngine {
    class DebugUI;
    class GameObjectComponent {

    private:
        friend class DebugUI;

        GameObjectComponent* parent_;

    protected:
        std::string name;

        std::list<std::shared_ptr<GameObjectComponent>> Components;

    public:

        virtual void addComponent(std::shared_ptr<GameObjectComponent> component) {
            Components.push_back(component);
            component->SetParent(this);
        }
        virtual void removeComponent(std::shared_ptr<GameObjectComponent> component) {
            Components.remove(component);
            component->SetParent(this);
        }

        virtual ~GameObjectComponent() {}

        void SetParent(GameObjectComponent* parent) {
            this->parent_ = parent;
        }
        GameObjectComponent* GetParent() const {
            return this->parent_;
        }


        virtual bool IsComposite() const {
            return Components.size() != 0;
        }

        std::string GetName() {
            return name;
        }
        void SetName(std::string name) {
            this->name = name;
        }

        int GetSize() {
            return Components.size();
        }
    };
}