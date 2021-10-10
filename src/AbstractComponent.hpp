#pragma once
#include <memory>
#include <string>
#include <list>
namespace BEbraEngine {
    class DebugUI;
    class AbstractComponent {

    private:
        friend class DebugUI;

        AbstractComponent* parent_;

    protected:
        std::string name;

        std::list<std::shared_ptr<AbstractComponent>> Components;

    public:

        virtual ~AbstractComponent() {}

        void SetParent(AbstractComponent* parent) {
            this->parent_ = parent;
        }
        AbstractComponent* GetParent() const {
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
        virtual void _addComponent(std::shared_ptr<AbstractComponent> component) {}
        virtual void _removeComponent(std::shared_ptr<AbstractComponent> component) {}
    };
}