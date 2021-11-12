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
        template<typename T>
        T* GetComponent() {
            for (auto component : Components) {
                if (dynamic_cast<T*>(component.get())) {
                    return static_cast<T*>(component.get());
                }
            }
            throw std::exception();
        }

        template<typename T>
        std::optional<T*> getComponent() {
            for (auto component : Components) {
                if (dynamic_cast<T*>(component.get())) {
                    return std::optional<T*>(
                        static_cast<T*>(component.get())
                        );
                }
            }
            return std::optional<T*>();
        }

        bool IsComposite() const override;

        GameObject();

        ~GameObject();

    };
}

