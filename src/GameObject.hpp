
#pragma once
#include "AbstractComponent.hpp"
#include "stdafx.h"
#include <typeinfo>
#include "Vector3.hpp"

namespace BEbraEngine {
    class GameObjectFactory;

}
namespace BEbraEngine {
    class GameObjectFactory;

    class GameObject : public GameObjectComponent {

    public:
        static void SetFactory(GameObjectFactory* factory);

        static std::shared_ptr<GameObject> New(const Vector3& position = Vector3(0));

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

        bool IsComposite() const override;

        GameObject();

        ~GameObject();

    private:
        static GameObjectFactory* factory;


    };
}

