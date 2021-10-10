#pragma once
#include "AbstractComponent.hpp"
#include <list>
#include <typeinfo>
#include "GameObjectFactory.hpp"
#include <glm/glm.hpp>
#include <iostream>
namespace BEbraEngine {
    class GameObjectFactory;

    class GameObject : public AbstractComponent {
    private:
        static GameObjectFactory* factory;

    protected:

        void _addComponent(std::shared_ptr<AbstractComponent> component) override;

        void _removeComponent(std::shared_ptr<AbstractComponent> component) override;

    public:
        static void SetFactory(GameObjectFactory* factory);

        static std::shared_ptr<GameObject> New(glm::vec3 position = glm::vec3(0));

        static void Destroy(std::shared_ptr<GameObject> object);

        void Destroy();

        template<typename T>
        T* GetComponent() {
            for (auto component : Components) {
                if (typeid(*component.get()) == typeid(T))
                    return static_cast<T*>(component.get());
            }
            throw std::exception();
        }



        void AddComponent(std::shared_ptr<AbstractComponent> component);

        bool IsComposite() const override;

        GameObject();

        ~GameObject();

    };
}

