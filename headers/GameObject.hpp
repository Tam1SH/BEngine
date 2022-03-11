#pragma once
#include "stdafx.h"
#include "platform.hpp"
#include "GameComponent.hpp"

#include <typeinfo>
#include "Vector3.hpp"

#include "Debug.hpp"

using BE_STD::shared_ptr;
using BE_STD::string;
using BE_STD::optional;
namespace BEbraEngine {


    class GameObject : public GameComponent { 
        DEBUG_DESTROY_CHECK_DECL()
    public:

        void destroy(IVisitorGameComponentDestroyer& destroyer) override;

        template<typename T, class _ = typename BE_STD::enable_if<BE_STD::is_base_of<GameComponent, T>::value>::type>
        shared_ptr<T> getComponentCheckedPtr() const noexcept {
            for (auto& component : components_) {
                if (std::dynamic_pointer_cast<T>(component)) {
                    return std::static_pointer_cast<T>(component);
                }
            }
            throw std::exception();
        }

        template<typename T, class _ = typename BE_STD::enable_if<BE_STD::is_base_of<GameComponent, T>::value>::type>
        T& getComponentChecked() const noexcept {
            for (auto& component : components_) {
                if (dynamic_cast<T*>(component.get())) {
                    return *static_cast<T*>(component.get());
                }
            }
            throw std::exception();
        }

        template<typename T, class _ = typename BE_STD::enable_if<BE_STD::is_base_of<GameComponent, T>::value>::type>
        optional<T*> getComponent() const noexcept {
            for (auto& component : components_) {
                if (dynamic_cast<T*>(component.get())) {
                    return optional<T*>(static_cast<T*>(component.get()));
                }
            }
            return optional<T*>();
        }
        GameComponent* getComponentByName(const string& name) const noexcept;


        bool isComposite() const noexcept override;

        GameObject() noexcept;

        GameObject(const string& name) noexcept;

        ~GameObject() noexcept;

    };
}

