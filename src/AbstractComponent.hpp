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
    protected:
        virtual void _addComponent(std::shared_ptr<GameObjectComponent> component) {}
        virtual void _removeComponent(std::shared_ptr<GameObjectComponent> component) {}
    };
}