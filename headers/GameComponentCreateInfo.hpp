#include "RenderObject.hpp"
#include "Transform.hpp"
#include "RigidBoby.hpp"
#include "Collider.hpp"

namespace BEbraEngine {
    class GameComponentCreateInfo {
    public:
        const Transform::TransformCreateInfo* transformInfo;
        const Collider::ColliderCreateInfo* colliderInfo;
        const RigidBody::RigidBodyCreateInfo* rigidBodyInfo;
        const RenderObject::RenderObjectCreateInfo* renderInfo;
    };
}