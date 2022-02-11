#pragma once

#include "IVisitorGameComponentDestroyer.hpp"
namespace BEbraEngine {

	class IRenderObjectFactory;
	class ColliderFactory;
	class RigidBodyFactory;
}
namespace BEbraEngine {


	
	class GameComponentDestroyer : public IVisitorGameComponentDestroyer
	{
	public:
		GameComponentDestroyer(
			IRenderObjectFactory& renderFactory,
			ColliderFactory& colliderFactory,
			RigidBodyFactory& rigidBodyFactory);

		void destroyGameObject(GameObject& comp) const override;

		void destroyPointLightComponent(PointLight& comp) const override;

		void destroyDirectionLightComponent(DirectionLight& comp) const override;

		void destroyRenderComponent(RenderObject& comp) const override;

		void destroyRigidBodyComponent(RigidBody& comp) const override;

		void destroyColliderComponent(Collider& comp) const override;
	
		void destroyMaterialComponent(Texture& comp) const override;

		void destroyTransformComponent(Transform& comp) const override;

		void destroyCameraComponent(SimpleCamera& comp) const override;

	private:
		IRenderObjectFactory* renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;


	};
	
}
