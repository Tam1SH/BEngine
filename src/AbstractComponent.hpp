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
            component->setParent(this);
        }
        virtual void removeComponent(std::shared_ptr<GameObjectComponent> component) {
            Components.remove(component);
            component->setParent(this);
        }

        virtual ~GameObjectComponent() {}

        void setParent(GameObjectComponent* parent) {
            this->parent_ = parent;
        }
        GameObjectComponent* getParent() const {
            return this->parent_;
        }


        virtual bool isComposite() const {
            return Components.size() != 0;
        }

        std::string getName() {
            return name;
        }
        void setName(std::string name) {
            this->name = name;
        }

        int getSize() {
            return Components.size();
        }
    };
}