#include "RenderObject.hpp"
#include "Transform.hpp"
#include "RigidBoby.hpp"
#include "Collider.hpp"

namespace BEbraEngine {
    class GameComponentCreateInfo {
    public:
        const Transform::CreateInfo* transformInfo;
        const Collider::CreateInfo* colliderInfo;
        const RigidBody::CreateInfo* rigidBodyInfo;
        const RenderObject::CreateInfo* renderInfo;
    };
}