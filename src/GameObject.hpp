#pragma once
#include "AbstractComponent.hpp"
#include "stdafx.h"
#include <typeinfo>
#include "Vector3.hpp"
#include "Debug.hpp"
#include "RenderObject.hpp"
#include "Collider.hpp"
#include "RigidBoby.hpp"
#include "Transform.hpp"

namespace BEbraEngine {


    class GameObject : public GameObjectComponent { DEBUG_DESTROY_CHECK_DECL()
    public:
        struct GameObjectCreateInfo {
            
            const Transform::TransformCreateInfo* transformInfo;
            const Collider::ColliderCreateInfo* colliderInfo;
            const RigidBody::RigidBodyCreateInfo* rigidBodyInfo;
            const RenderObject::RenderObjectCreateInfo* renderInfo;
            const PointLight::PointLightCreateInfo* pointLightInfo;
            const DirectionLight::DirectionLightCreateInfo* directionLightInfo;

        };
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

        std::shared_ptr<GameObjectComponent> getComponentByName(const std::string& name) {
            for (auto component : Components) {
                std::string componentName = typeid(*component.get()).name();
                
                if (componentName.find(name) != std::string::npos) {
                    return component;
                }
            }
            return std::shared_ptr<GameObjectComponent>();
        }

        bool isComposite() const override;

        GameObject();

        GameObject(const std::string& name);

        ~GameObject();

    };
}

