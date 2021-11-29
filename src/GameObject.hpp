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
        std::shared_ptr<T> getComponent() {
            for (auto component : Components) {
                if (std::dynamic_pointer_cast<T>(component)) {
                    return std::static_pointer_cast<T>(component);
                }
            }
            return std::shared_ptr<T>();
        }

        bool isComposite() const override;

        GameObject();

        ~GameObject();

    };
}

