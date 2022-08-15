#include "platform.hpp"

export module VisitorGameComponentDestroyer;
import RenderObjects;
import Collider;
import RigidBody;
import Camera;
import Texture;
import GameObject;

import <memory>;

import Transform;
using std::shared_ptr;

namespace BEbraEngine {
}


namespace BEbraEngine {

	export class VisitorGameComponentDestroyer {
	public:
		virtual void destroyGameObject(GameObject& comp) = 0;
		virtual void destroyPointLightComponent(Light& comp) = 0;
		virtual void destroyDirectionLightComponent(DirectionLight& comp) = 0;


		virtual void destroyRenderComponent(RenderObject& comp) = 0;
		virtual void destroyRigidBodyComponent(RigidBody& comp) = 0;
		virtual void destroyColliderComponent(Collider& comp) = 0;
		virtual void destroyTextureComponent(Texture& comp) = 0;
		virtual void destroyTextureComponentAsync(shared_ptr<Texture> comp) = 0;
		virtual void destroyMaterialComponent(Material& comp) = 0;
		virtual void destroyTransformComponent(Transform& comp) = 0;
		virtual void destroyCameraComponent(SimpleCamera& comp) = 0;

		virtual ~VisitorGameComponentDestroyer() noexcept {}
		VisitorGameComponentDestroyer() noexcept {}
	};
}