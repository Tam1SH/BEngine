#pragma once
#include <memory>
#include <string>
#include <list>
namespace BEbraEngine {
    class IVisitorGameComponentDestroyer;
}
namespace BEbraEngine {

    class GameComponent {

    private:
        friend class DebugUI;

        GameComponent* parent_{};

    protected:
        std::string name;

        std::list<std::shared_ptr<GameComponent>> components_;

    public:

        virtual ~GameComponent() {}
        GameComponent() {}

        virtual void destroy(IVisitorGameComponentDestroyer* destroyer) = 0;

        virtual void addComponent(std::shared_ptr<GameComponent> component) {
            components_.push_back(component);
            component->setParent(this);
        }
        virtual void removeComponent(std::shared_ptr<GameComponent> component) {
            components_.remove(component);

        }

        

        void setParent(GameComponent* parent) {
            this->parent_ = parent;
        }

        GameComponent* getParent() const {
            return this->parent_;
        }


        virtual bool isComposite() const {
            return components_.size() != 0;
        }

        std::string getName() {
            return name;
        }
        void setName(std::string name) {
            this->name = name;
        }

        size_t getSize() {
            return components_.size();
        }
    };
}