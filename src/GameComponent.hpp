#pragma once
#include <memory>
#include <string>
#include <list>

using std::shared_ptr;
using std::string;
using std::list;

namespace BEbraEngine {
    class IVisitorGameComponentDestroyer;
}

namespace BEbraEngine {

    class GameComponent {
    public:

        virtual ~GameComponent() {}
        GameComponent() {}

        virtual void destroy(IVisitorGameComponentDestroyer& destroyer) = 0;

        virtual void addComponent(shared_ptr<GameComponent> component) {
            components_.push_back(component);
            component->setParent(*this);
        }

        virtual void removeComponent(GameComponent& component) {
          //  components_.remove(component);
        }

        void setParent(GameComponent& parent) { this->parent_ = &parent; }

        GameComponent& getParent() const { return *this->parent_; }

        virtual bool isComposite() const { return components_.size() != 0; }

        string& getName() { return name_; }

        void setName(const string& name) { this->name_ = name; }

        size_t getSize() { return components_.size(); }

    protected:
        string name_;

        list<shared_ptr<GameComponent>> components_;

    private:

        GameComponent* parent_{};


    };
}