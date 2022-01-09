#pragma once
#include "GameComponent.hpp"
#include "stdafx.h"
#include <typeinfo>
#include "Vector3.hpp"

#ifdef _DEBUG
#include "Debug.hpp"
#endif 


namespace BEbraEngine {
}
namespace BEbraEngine {


    class GameObject : public GameComponent { 
#ifdef _DEBUG
        DEBUG_DESTROY_CHECK_DECL()
#endif
    public:

        void destroy(IVisitorGameComponentDestroyer* destroyer) override;

        template<typename T>
        std::shared_ptr<T> getComponent() {
            for (auto component : components_) {
                if (std::dynamic_pointer_cast<T>(component)) {
                    return std::static_pointer_cast<T>(component);
                }
            }
            return std::shared_ptr<T>();
        }

        std::shared_ptr<GameComponent> getComponentByName(const std::string& name) {
            for (auto component : components_) {

                //TODO: нестрогое сравнение названий классов, в будущем могу на этом пососать.
                std::string componentName = typeid(*component.get()).name();
                
                if (componentName.find(name) != std::string::npos) {
                    return component;
                }
            }
            return std::shared_ptr<GameComponent>();
        }

        bool isComposite() const override;

        GameObject();

        GameObject(const std::string& name);

        ~GameObject();

    };
}

