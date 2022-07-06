#include <boost/filesystem.hpp>
export module GameComponentDestroyer;
import IVisitorGameComponentDestroyer;
import IRenderObjectFactory;
import ColliderFactory;
import RigidBodyFactory;
import <memory>;



using std::shared_ptr;

namespace BEbraEngine {

}
namespace BEbraEngine {


	
	export class GameComponentDestroyer : public IVisitorGameComponentDestroyer
	{
	public:
		GameComponentDestroyer(
			IRenderObjectFactory& renderFactory,
			ColliderFactory& colliderFactory,
			RigidBodyFactory& rigidBodyFactory);
		
		void destroyGameObject(GameObject& comp) override;

		void destroyPointLightComponent(Light& comp);

		void destroyDirectionLightComponent(DirectionLight& comp);

		void destroyTextureComponentAsync(shared_ptr<Texture> comp);

		void destroyRenderComponent(RenderObject& comp);

		void destroyRigidBodyComponent(RigidBody& comp);

		void destroyColliderComponent(Collider& comp);
	
		void destroyTextureComponent(Texture& comp);

		void destroyMaterialComponent(Material& comp);

		void destroyTransformComponent(Transform& comp);

		void destroyCameraComponent(SimpleCamera& comp);

	private:
		IRenderObjectFactory* renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;


	};

}
