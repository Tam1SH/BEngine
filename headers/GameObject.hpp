#pragma once
#include "stdafx.h"
#include "platform.hpp"
#include "GameComponent.hpp"

#include <typeinfo>
#include "Vector3.hpp"

#include "Debug.hpp"

using BE_STD::shared_ptr;
using BE_STD::string;

namespace BEbraEngine {


    class GameObject : public GameComponent { 
        DEBUG_DESTROY_CHECK_DECL()
    public:

        void destroy(IVisitorGameComponentDestroyer& destroyer) override;

        template<typename T, class _ = typename BE_STD::enable_if<BE_STD::is_base_of<GameComponent, T>::value>::type>
        T* getComponent() const {
            for (auto& component : components_) {
                if (dynamic_cast<T*>(component.get())) {
                    return static_cast<T*>(component.get());
                }
            }
            return nullptr;
        }

        GameComponent* getComponentByName(const string& name) const noexcept;


        bool isComposite() const noexcept override;

        GameObject() noexcept;

        GameObject(const string& name) noexcept;

        ~GameObject() noexcept;

    };
}

