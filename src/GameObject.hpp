#pragma once
#include "AbstractComponent.hpp"
#include "stdafx.h"
#include <typeinfo>
#include "Vector3.hpp"
#include "Debug.hpp"


namespace BEbraEngine {


    class GameObject : public GameObjectComponent { DEBUG_DESTROY_CHECK_DECL()
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

        GameObject(const std::string& name);

        ~GameObject();

    };
}

