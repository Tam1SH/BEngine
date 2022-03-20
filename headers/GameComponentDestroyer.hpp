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

		void destroyGameObject(GameObject& comp) override;

		void destroyPointLightComponent(Light& comp) override;

		void destroyDirectionLightComponent(DirectionLight& comp) override;

		void destroyTextureComponentAsync(shared_ptr<Texture> comp) override;

		void destroyRenderComponent(RenderObject& comp) override;

		void destroyRigidBodyComponent(RigidBody& comp) override;

		void destroyColliderComponent(Collider& comp) override;
	
		void destroyTextureComponent(Texture& comp) override;

		void destroyMaterialComponent(Material& comp) override;

		void destroyTransformComponent(Transform& comp) override;

		void destroyCameraComponent(SimpleCamera& comp) override;

	private:
		IRenderObjectFactory* renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;




	};
	
}
