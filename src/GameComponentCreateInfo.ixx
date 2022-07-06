export module GameComponentCreateInfo;

import RenderObjects;
import RigidBody;
import Collider;
import Transform;
namespace BEbraEngine {
    export class GameComponentCreateInfo {
    public:
        const Transform::CreateInfo* transformInfo;
        const ColliderCreateInfo* colliderInfo;
        const RigidBodyCreateInfo* rigidBodyInfo;
        const RenderObjectCreateInfo* renderInfo;
    };
}