#pragma once
#include "GameComponent.hpp"
#include "stdafx.h"
#include <typeinfo>
#include "Vector3.hpp"

#include "Debug.hpp"

using std::shared_ptr;
using std::string;

namespace BEbraEngine {


    class GameObject : public GameComponent { 
        DEBUG_DESTROY_CHECK_DECL()
    public:

        void destroy(IVisitorGameComponentDestroyer& destroyer) override;

        template<typename T, class _ = typename std::enable_if<std::is_base_of<GameComponent, T>::value>::type>
        T* getComponent() {
            for (auto& component : components_) {
                if (dynamic_cast<T*>(component.get())) {
                    return static_cast<T*>(component.get());
                }
            }
            return nullptr;
        }

        GameComponent* getComponentByName(const string& name) {
            for (auto& component : components_) {

                //TODO: нестрогое сравнение названий классов, в будущем могу на этом пососать.
                string componentName = typeid(*component).name();
                
                if (componentName.find(name) != string::npos) {
                    return component.get();
                }
            }
            return nullptr;
        }

        bool isComposite() const override;

        GameObject();

        GameObject(const string& name);

        ~GameObject();

    };
}

